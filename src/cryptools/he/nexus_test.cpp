#include "nexus-api.h"
#include <chrono>
using namespace std;
using namespace nexus;
using namespace std::chrono;

int main() {
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

    CKKSEvaluator ckks(context, encryptor, decryptor, encoder, evaluator, SCALE,
                                 relin_keys, galois_keys);

    vector<double> v1 = {0.1, 0.2, 0.3, -0.4, 0.5, -0.9};
    vector<double> v2 = {0.3, -0.1, 0.3, 0.4, -0.5, 0.7};
    // vector<double> value = {1, 2, 3, -4, 5, -6};
    size_t size = v1.size();
    Plaintext pt1, pt2;
    encoder.encode(v1, SCALE, pt1);
    encoder.encode(v2, SCALE, pt2);
    Ciphertext x, y;
    encryptor.encrypt(pt1, x);
    encryptor.encrypt(pt2, y);

    Ciphertext ct_out = ckks.ge(x, y);
    Plaintext pt_out;
    decryptor.decrypt(ct_out, pt_out);
    vector<double> out;
    encoder.decode(pt_out, out);
    for (int i = 0; i < size; i++) {
        std::cout << out[i] << std::endl;
    }
}