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

#include "argmax.h"
#include "config.h"
#include "emp-tool.h"
#include "gelu.h"
#include "layer_norm.h"
#include "matrix_mul.h"
#include "softmax.h"

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
class NEXUS_op {
    vector<string> TEST_TARGETS = {"MatMul", "Argmax", "GELU", "LayerNorm", "SoftMax"};

public:
    static const Type type = Type::NEXUS;
    int party;
    // CheetahLinear* linear;
    typedef vector<vector<vector<double>>> Type;

    NEXUS_op(int party, NetIO* io, unsigned long logN = 13, vector<int> MM_COEFF_MODULI = {60, 40, 60},
             double scale = pow(2.0, 40));

    ~NEXUS_op();

    void fc(vector<vector<vector<double>>>& input, const vector<vector<vector<double>>>& weight,
            vector<vector<vector<double>>>& output);

    void argmax();

    void gelu(const vector<vector<vector<double>>>& input, vector<vector<vector<double>>>& output);

    void ln(const vector<vector<vector<double>>>& input, vector<vector<vector<double>>>& output);

    void softmax(const vector<vector<vector<double>>>& input, vector<vector<vector<double>>>& output);

private:
    size_t poly_modulus_degree, scale;
    EncryptionParameters* parms;
    SEALContext* context;
    KeyGenerator* keygen;
    SecretKey secret_key;
    PublicKey public_key;
    RelinKeys relin_keys;

    GaloisKeys galois_keys;

    Encryptor* encryptor;
    CKKSEncoder* encoder;
    Evaluator* evaluator;
    Decryptor* decryptor;

    CKKSEvaluator* ckks_evaluator;
    Bootstrapper* bootstrapper;

    MMEvaluator* mme;
    ArgmaxEvaluator* argmax_evaluator;
    GeLUEvaluator* gelu_evaluator;
    LNEvaluator* ln_evaluator;
    SoftmaxEvaluator* softmax_evaluator;
};