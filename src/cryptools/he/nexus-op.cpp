#include "nexus-op.h"

#include <seal/ciphertext.h>

#include <cstddef>

#include "Bootstrapper.h"
#include "argmax.h"

NEXUS_op::NEXUS_op(int party, NetIO* io, unsigned long logN, vector<int> COEFF_MODULI,
                   double _scale)
    : OP(party, MPCType::NEXUS), scale(_scale) {
    // QuickMax: 17
    int main_mod_count = 17; // Mod count after bootstrapping: 18
    // Subsum 1 + coefftoslot 2 + ModReduction 9 + slottocoeff 2
    int bs_mod_count = 14;
    int total_level = main_mod_count + bs_mod_count;

    long boundary_K = 25;
    long deg = 59;
    long scale_factor = 2;
    long inverse_deg = 1;
    long loge = 10;

    this->logN = logN;
    poly_modulus_degree = 1 << logN;
    parms = new EncryptionParameters(scheme_type::ckks);
    parms->set_poly_modulus_degree(poly_modulus_degree);
    parms->set_coeff_modulus(CoeffModulus::Create(poly_modulus_degree, COEFF_MODULI));
    context = new SEALContext(*parms, true, sec_level_type::none);

    keygen = new KeyGenerator(*context);
    secret_key = keygen->secret_key();
    keygen->create_public_key(public_key);
    keygen->create_galois_keys(galois_keys);
    keygen->create_relin_keys(relin_keys);

    std::vector<std::uint32_t> rots;
    for (int i = 0; i < logN; i++) {
        rots.push_back((poly_modulus_degree + exponentiate_uint(2, i)) / exponentiate_uint(2, i));
    }
    keygen->create_galois_keys(rots, mm_galois_keys);

    encryptor = new Encryptor(*context, public_key);
    encoder = new CKKSEncoder(*context);
    evaluator = new Evaluator(*context, *encoder);
    decryptor = new Decryptor(*context, secret_key);

    ckks_evaluator = new CKKSEvaluator(*context, *encryptor, *decryptor, *encoder, *evaluator,
                                       scale, relin_keys, galois_keys);
    mm_ckks_evaluator = new CKKSEvaluator(*context, *encryptor, *decryptor, *encoder, *evaluator,
                                          scale, relin_keys, mm_galois_keys);
    bootstrapper = new Bootstrapper(loge, logN - 2, logN - 1, total_level, scale, boundary_K, deg,
                                    scale_factor, inverse_deg, *context, *keygen, *encoder,
                                    *encryptor, *decryptor, *evaluator, relin_keys, mm_galois_keys);

    mme = new MMEvaluator(*ckks_evaluator);
    argmax_evaluator = new ArgmaxEvaluator(*ckks_evaluator, *bootstrapper);
    gelu_evaluator = new GeLUEvaluator(*ckks_evaluator);
    ln_evaluator = new LNEvaluator(*ckks_evaluator);
    softmax_evaluator = new SoftmaxEvaluator(*ckks_evaluator);
}

NEXUS_op::~NEXUS_op() {
    delete parms;
    delete context;
    delete keygen;
    delete encryptor;
    delete encoder;
    delete evaluator;
    delete decryptor;
    delete ckks_evaluator;
    delete mm_ckks_evaluator;
    delete bootstrapper;
    delete mme;
    delete argmax_evaluator;
    delete gelu_evaluator;
    delete ln_evaluator;
    delete softmax_evaluator;
}

void NEXUS_op::fc(Data& input, const Data& weight, Data& output) {
    auto num_feature = input.NexusData.size(), dim1 = input.NexusData[0].size(),
         dim2 = input.NexusData[0][0].size(), dim3 = weight.NexusData[0][0].size();

    output = Data();
    output.NexusData = vector<vector<vector<double>>>(
        num_feature, vector<vector<double>>(dim1, vector<double>(dim3, 0.0)));

    for (auto nf = 0; nf < num_feature; nf++) {
        vector<vector<double>> row_pack;
        vector<double> row_ct(poly_modulus_degree / 2, 0.0);
        for (auto i = 0; i < dim2 * dim3; i++) {
            int row = i / dim3;
            int col = i % dim3;
            row_ct[i % poly_modulus_degree / 2] = weight.NexusData[nf][row][col];
            if (i % poly_modulus_degree / 2 == (poly_modulus_degree / 2 - 1) ||
                i == dim2 * dim3 - 1) {
                row_pack.push_back(row_ct);
            }
        }

        vector<Ciphertext> res;
        mme->matrix_mul(input.NexusData[nf], row_pack, dim3, res);

        size_t res_size = res.size();
        vector<Plaintext> res_pt(res_size);
        vector<vector<double>> mm_res(res_size);
        for (auto i = 0; i < res_size; i++) {
            mm_ckks_evaluator->decryptor->decrypt(res[i], res_pt[i]);
            mm_ckks_evaluator->encoder->decode(res_pt[i], mm_res[i]);
        }
        for (auto i = 0; i < dim1 * dim3; i++) {
            int row1 = i / dim3;
            int col1 = i % dim3;
            int row2 = i / poly_modulus_degree;
            int col2 = i % poly_modulus_degree;
            output.NexusData[nf][row1][col1] = mm_res[row2][col2];
        }
    }
}

void NEXUS_op::argmax(const Data& input, Data& outpu) {}

void NEXUS_op::gelu(const Data& input, Data& output) {
    size_t num_feature = input.NexusData.size(), dim1 = input.NexusData[0].size(),
           dim2 = input.NexusData[0][0].size();

    output = Data();
    output.NexusData = vector<vector<vector<double>>>(
        num_feature, vector<vector<double>>(dim1, vector<double>(dim2, 0.0)));

    for (size_t i = 0; i < num_feature; i++) {
        for (size_t j = 0; j < dim1; j++) {
            Plaintext plain_input, plain_output;
            Ciphertext cipher_input, cipher_output;
            ckks_evaluator->encoder->encode(input.NexusData[i][j], scale, plain_input);
            ckks_evaluator->encryptor->encrypt(plain_input, cipher_input);

            gelu_evaluator->gelu(cipher_input, cipher_output);

            vector<double> output_vector;
            ckks_evaluator->decryptor->decrypt(cipher_output, plain_output);
            ckks_evaluator->encoder->decode(plain_output, output_vector);

            std::copy(output_vector.begin(), output_vector.begin() + dim2,
                      output.NexusData[i][j].begin());
        }
    }
}

void NEXUS_op::ln(const Data& input, Data& output) {
    size_t num_feature = input.NexusData.size(), dim1 = input.NexusData[0].size(),
           dim2 = input.NexusData[0][0].size();

    output = Data();
    output.NexusData = vector<vector<vector<double>>>(
        num_feature, vector<vector<double>>(dim1, vector<double>(dim2, 0.0)));

    for (size_t i = 0; i < num_feature; i++) {
        for (size_t j = 0; j < dim1; j++) {
            Plaintext plain_input, plain_output;
            Ciphertext cipher_input, cipher_output;
            ckks_evaluator->encoder->encode(input.NexusData[i][j], scale, plain_input);
            ckks_evaluator->encryptor->encrypt(plain_input, cipher_input);

            ln_evaluator->layer_norm(cipher_input, cipher_output, 1024);

            vector<double> output_vector;
            ckks_evaluator->decryptor->decrypt(cipher_output, plain_output);
            ckks_evaluator->encoder->decode(plain_output, output_vector);

            std::copy(output_vector.begin(), output_vector.begin() + dim2,
                      output.NexusData[i][j].begin());
        }
    }
}

void NEXUS_op::softmax(const Data& input, Data& output) {
    size_t num_feature = input.NexusData.size(), dim1 = input.NexusData[0].size(),
           dim2 = input.NexusData[0][0].size();

    output = Data();
    output.NexusData = vector<vector<vector<double>>>(
        num_feature, vector<vector<double>>(dim1, vector<double>(dim2, 0.0)));

    for (size_t i = 0; i < num_feature; i++) {
        for (size_t j = 0; j < dim1; j++) {
            Plaintext plain_input, plain_output;
            Ciphertext cipher_input, cipher_output;
            ckks_evaluator->encoder->encode(input.NexusData[i][j], scale, plain_input);
            ckks_evaluator->encryptor->encrypt(plain_input, cipher_input);

            softmax_evaluator->softmax(cipher_input, cipher_output, 128);

            vector<double> output_vector;
            ckks_evaluator->decryptor->decrypt(cipher_output, plain_output);
            ckks_evaluator->encoder->decode(plain_output, output_vector);

            std::copy(output_vector.begin(), output_vector.begin() + dim2,
                      output.NexusData[i][j].begin());
        }
    }
}