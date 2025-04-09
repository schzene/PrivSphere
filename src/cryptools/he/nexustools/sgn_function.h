
#pragma once

#include <seal/seal.h>

#include "ckks_evaluator.h"

using namespace std;
using namespace seal;
namespace nexus {
class SgnFuncEvaluator {
private:
    CKKSEvaluator* ckks = nullptr;

public:
    SgnFuncEvaluator(CKKSEvaluator& ckks) {
        this->ckks = &ckks;
    }

    void sgnfunc(Ciphertext x, int d_g, int d_f, int sgn_factor, Ciphertext dest);
};
}  // namespace nexus