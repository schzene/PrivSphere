#include "sgn_function.h"

void SgnFuncEvaluator::sgnfunc(Ciphertext x, int d_g, int d_f, int sgn_factor, Ciphertext dest) {
    dest = ckks->sgn_eval(x, 2, 2);
}