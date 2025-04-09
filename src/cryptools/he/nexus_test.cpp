#include "nexus-op.h"
#include <chrono>
using namespace std;
using namespace nexus;
using namespace std::chrono;

int main(int argc, const char** argv) {
    vector<int> COEFF_MODULI = {58, 40, 40, 40, 40, 40, 40, 40, 40, 40,
                                40, 40, 40, 40, 40, 40, 40, 40, 40, 58};
    long logN = 16;
    size_t poly_modulus_degree = 1 << logN;
    double SCALE = pow(2.0, 40);

    EncryptionParameters parms(scheme_type::ckks);
    parms.set_poly_modulus_degree(poly_modulus_degree);
    parms.set_coeff_modulus(CoeffModulus::Create(poly_modulus_degree, COEFF_MODULI));

    SEALContext context(parms, true, sec_level_type::none);

    KeyGenerator keygen(context);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);
    RelinKeys relin_keys;
    keygen.create_relin_keys(relin_keys);
    GaloisKeys galois_keys;
    keygen.create_galois_keys(galois_keys);

    Encryptor encryptor(context, public_key);
    CKKSEncoder encoder(context);
    Evaluator evaluator(context, encoder);
    Decryptor decryptor(context, secret_key);

    CKKSEvaluator ckks(context, encryptor, decryptor, encoder, evaluator, SCALE, relin_keys,
                       galois_keys);

    // vector<double> v1 = {0.1, 0.2, 0.3, -0.4, 0.5, -0.9};
    // vector<double> v2 = {0.3, -0.1, 0.3, 0.4, -0.5, 0.7};
    // vector<double> value = {1, 2, 3, -4, 5, -6};
    // size_t size = v1.size();
    size_t size = poly_modulus_degree / 2;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(-1, 1);
    vector<double> v1(size), v2(size);

    sci::NetIO* io;
    if (argc > 1) {
        io = new sci::NetIO("127.0.0.1", 32000);
        for (size_t i = 0; i < size; i++) {
            v1[i] = dist(gen);
            v2[i] = dist(gen);
        }
        io->send_data(v1.data(), size * sizeof(double));
        io->send_data(v2.data(), size * sizeof(double));
    } else {
        io = new sci::NetIO(nullptr, 32000);
        io->recv_data(v1.data(), size * sizeof(double));
        io->recv_data(v2.data(), size * sizeof(double));
    }
    Plaintext pt1, pt2;
    encoder.encode(v1, SCALE, pt1);
    encoder.encode(v2, SCALE, pt2);
    // Ciphertext x, y;
    // encryptor.encrypt(pt1, x);
    // encryptor.encrypt(pt2, y);

    // Ciphertext ct_out = ckks.ge(x, y);
    // Plaintext pt_out;
    // decryptor.decrypt(ct_out, pt_out);
    // vector<double> out;
    // encoder.decode(pt_out, out);
    // for (int i = 0; i < size; i++) {
    //     std::cout << out[i] << std::endl;
    // }
    Ciphertext x, y;
    if (argc > 1) {
        std::cout << "size of data: " << size << "\n";
        encryptor.encrypt(pt1, x);
        send_ct(io, &x);
        recv_ct(io, &y, &context);
        Plaintext d_y;
        decryptor.decrypt(y, d_y);
        vector<double> ret;
        encoder.decode(d_y, ret);
        bool err = false;
        for (size_t i = 0; i < size; i++) {
            if (abs(ret[i] - (v1[i] + v2[i])) > 1e-5) {
                std::cout << "Error: " << ret[i] << " != " << v1[i] + v2[i] << std::endl;
                err = true;
            }
        }
        if (!err) {
            std::cout << "test passed\n";
        }
    } else {
        recv_ct(io, &x, &context);
        evaluator.add_plain(x, pt2, y);
        send_ct(io, &y);
    }
}