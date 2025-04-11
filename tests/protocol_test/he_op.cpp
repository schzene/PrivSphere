#include "config.h"
#include <cassert>
#include <iostream>
#include <seal/ciphertext.h>
#include <seal/plaintext.h>
#include <seal/seal.h>
#include <vector>

using namespace seal;
using namespace std;

#define min(a, b) ((a) < (b) ? (a) : (b))

map<string, int> op_map = {
    {"add", 0},
    {"sub", 1},
    {"mul", 2}
};

int get_op(const string& op_name) {
    auto it = op_map.find(op_name);
    if (it != op_map.end()) {
        return it->second;
    } else {
        cerr << "Invalid operation name: " << op_name << endl;
        exit(EXIT_FAILURE);
    }
}

int main(int argc, const char** argv) {
    assert(argc >= 2 && "Usage: ./he_add <op> <size>");

    int op = get_op(argv[1]);
    int size = atoi(argv[2]);

    long logN = 13;
    size_t poly_modulus_degree = 1 << logN;
    double scale = pow(2, 40);

    int cipher_size = (size / (poly_modulus_degree / 2)) + 1;

    EncryptionParameters parms(scheme_type::ckks);
    parms.set_poly_modulus_degree(poly_modulus_degree);
    parms.set_coeff_modulus(CoeffModulus::Create(poly_modulus_degree, {60, 40, 60}));

    SEALContext context(parms, true, sec_level_type::none);

    KeyGenerator keygen(context);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);

    Encryptor encryptor(context, public_key);
    CKKSEncoder encoder(context);
    Evaluator evaluator(context, encoder);
    Decryptor decryptor(context, secret_key);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(-1, 1);
    vector<double> a(size), b(size);
    for (int i = 0; i < size; i++) {
        a[i] = dist(gen);
        b[i] = dist(gen);
    }

    vector<Plaintext> pta(cipher_size), ptb(cipher_size);
    vector<Ciphertext> cta(cipher_size), ctb(cipher_size);

    for (int i = 0; i < cipher_size; i++) {
        vector<double> a_part(a.begin() + i * (poly_modulus_degree / 2),
                              a.begin() + min((i + 1) * poly_modulus_degree / 2, size));
        vector<double> b_part(b.begin() + i * (poly_modulus_degree / 2),
                              b.begin() + min((i + 1) * poly_modulus_degree / 2, size));
        encoder.encode(a_part, scale, pta[i]);
        encoder.encode(b_part, scale, ptb[i]);
        encryptor.encrypt(pta[i], cta[i]);
        encryptor.encrypt(ptb[i], ctb[i]);
    }

    Ciphertext ret;
    auto start = std::chrono::high_resolution_clock::now();
    switch (op) {
    case 0:
        for (int i = 0; i < cipher_size; i++) {
            evaluator.add(cta[i], ctb[i], ret);
        }
        break;
    case 1:
        for (int i = 0; i < cipher_size; i++) {
            evaluator.sub(cta[i], ctb[i], ret);
        }
        break;
    case 2:
        for (int i = 0; i < cipher_size; i++) {
            evaluator.multiply(cta[i], ctb[i], ret);
        }
        break;
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Size of data: " << size << std::endl;
    std::cout << "Ciphertext size: " << cipher_size << std::endl;
    std::cout << "Time of " << argv[1] << ": "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us"
              << std::endl;
    return 0;
}