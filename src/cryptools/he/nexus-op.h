#pragma once

#include <seal/context.h>
#include <seal/encryptionparams.h>
#include <seal/seal.h>
#include <seal/util/uintarith.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../emp/emp-tool.h"
#include "nexus-api.h"
#include "op.h"


using namespace std;
using namespace seal;
using namespace seal::util;
using namespace std::chrono;
using namespace nisl;
using namespace nexus;

/**
 * A simple NEXUS interface, with secondary encapsulation, makes it support PrivSphere's contex
 */
// "127.0.0.1"
//  = 12345
class NEXUS_op : public OP {
public:
    std::vector<std::string> OPs = {"fc", "argmax", "gelu", "ln", "softmax"};
    static const MPCType type    = MPCType::NEXUS;
    // CheetahLinear* linear;
    typedef vector<vector<vector<double>>> OPType;

    NEXUS_op(int party, NetIO* io, unsigned long logN = 13,
             vector<int> COEFF_MODULI = {58, 40, 40, 40, 40, 40, 40, 40, 40, 40,
                                         40, 40, 40, 40, 40, 40, 40, 40, 40, 58},
             double scale             = pow(2.0, 40));

    ~NEXUS_op();

    void fc(Data& input, const Data& weight, Data& output);

    void argmax(const Data& input, Data& outpu);

    void gelu(const Data& input, Data& output);

    void ln(const Data& input, Data& output);

    void softmax(const Data& input, Data& output);

private:
    unsigned long logN;

    size_t poly_modulus_degree, scale;
    EncryptionParameters* parms;
    SEALContext* context;
    KeyGenerator* keygen;
    SecretKey secret_key;
    PublicKey public_key;
    RelinKeys relin_keys;

    GaloisKeys mm_galois_keys, galois_keys;

    Encryptor* encryptor;
    CKKSEncoder* encoder;
    Evaluator* evaluator;
    Decryptor* decryptor;

    CKKSEvaluator *ckks_evaluator, *mm_ckks_evaluator;
    Bootstrapper* bootstrapper;

    MMEvaluator* mme;
    ArgmaxEvaluator* argmax_evaluator;
    GeLUEvaluator* gelu_evaluator;
    LNEvaluator* ln_evaluator;
    SoftmaxEvaluator* softmax_evaluator;
};