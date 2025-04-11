#include "FloatingPoint/fixed-point.h"
#include "data_process.h"
#include <iostream>
#include <seal/plaintext.h>
#define min(a, b) ((a) < (b) ? (a) : (b))

using namespace std;

map<string, int> op_map = {
    {"he2ss", 0},
    {"ss2he", 1},
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
    assert(argc >= 3 && "Usage: ./ss_add <party> <op> <size>");
    int party = atoi(argv[1]), op = get_op(argv[2]), size = atoi(argv[3]);
    assert(party == sci::ALICE || party == sci::BOB);

    sci::IOPack* iopack = new sci::IOPack(party, 32000);
    sci::OTPack* otpack = new sci::OTPack(iopack, party);

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

    switch (op) {
    case 0: {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dist(-1, 1);
        vector<double> a(size);
        for (int i = 0; i < size; i++) {
            a[i] = dist(gen);
        }
        vector<Plaintext> pt(cipher_size);
        vector<Ciphertext> ct(cipher_size);
        for (int i = 0; i < cipher_size; i++) {
            vector<double> a_part(a.begin() + i * (poly_modulus_degree / 2),
                                  a.begin() + min((i + 1) * poly_modulus_degree / 2, size));
            encoder.encode(a_part, scale, pt[i]);
            encryptor.encrypt(pt[i], ct[i]);
        }

        auto comm_start = iopack->get_comm();
        auto start = std::chrono::high_resolution_clock::now();
        Decryptor* dec_ptr = party == sci::ALICE ? &decryptor : nullptr;
        for (int i = 0; i < cipher_size; i++) {
            FixArray fa =
                HE2SS(party, ct[i], iopack->io, dec_ptr, &encoder, &evaluator, &context, scale);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto comm_end = iopack->get_comm();
        auto comm = comm_end - comm_start;

        std::cout << "Size of data: " << size << std::endl;
        std::cout << "Ciphertext size: " << cipher_size << std::endl;
        std::cout << "Time of " << argv[2] << ": "
                  << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
                  << " us" << std::endl;
        std::cout << "Communication: " << comm << " B" << std::endl;

        break;
    }
    case 1: {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<uint64_t> dist(0, 1ULL << nisl::ELL);
        vector<uint64_t> a(size);
        for (int i = 0; i < size; i++) {
            a[i] = dist(gen);
        }
        vector<FixArray> fa;
        for (int i = 0; i < cipher_size; i++) {
            int fix_size = poly_modulus_degree / 2;
            if (i == cipher_size - 1) {
                fix_size = size - (cipher_size - 1) * (poly_modulus_degree / 2);
            }
            FixArray fix(party, fix_size, true, ELL, SCALE);
            for (int j = 0; j < fix_size; j++) {
                fix.data[j] = a[i * (poly_modulus_degree / 2) + j];
            }
            fa.push_back(fix);
        }

        auto comm_start = iopack->get_comm();
        auto start = std::chrono::high_resolution_clock::now();
        Encryptor* enc_ptr = party == sci::ALICE ? &encryptor : nullptr;
        for (int i = 0; i < cipher_size; i++) {
            Ciphertext ct =
                SS2HE(fa[i], iopack->io, enc_ptr, &encoder, &evaluator, &context, scale);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto comm_end = iopack->get_comm();
        auto comm = comm_end - comm_start;

        std::cout << "Size of data: " << size << std::endl;
        std::cout << "Ciphertext size: " << cipher_size << std::endl;
        std::cout << "Time of " << argv[2] << ": "
                  << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
                  << " us" << std::endl;
        std::cout << "Communication: " << comm << " B" << std::endl;
        break;
    }
    }

    delete otpack;
    delete iopack;
    return 0;
}