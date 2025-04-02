#pragma once
#include "FloatingPoint/bool-data.h"
#include "Math/math-functions.h"
#include <config.h>

#include <vector>

using std::vector;
using namespace nisl;
using namespace sci;

class SS_op {
public:
    int party;
    IOPack* iopack;
    OTPack* otpack;
    // Equality* eq;
    // MillionaireWithEquality* mill_eq;
    AuxProtocols* aux;
    XTProtocol* xt;
    Truncation* trunc;
    LinearOT* mult;
    BoolOp* bool_op;

    SS_op(int party, IOPack* iopack, OTPack* otpack);
    ~SS_op();

    void add(vector<uint64_t>& x, vector<uint64_t>& y, vector<uint64_t>& out);
    void add(vector<uint64_t>& x, uint64_t y, vector<uint64_t>& out);

    inline void sub(vector<uint64_t>& x, vector<uint64_t>& y, vector<uint64_t>& out) {
        mul(y, (1ULL << (ELL - 1)) + 1, out);
        add(x, out, out);
    }
    
    inline void sub(vector<uint64_t>& x, uint64_t y, vector<uint64_t>& out) {
        uint64_t _y = y ^ (1ULL << (ELL - 1));
        add(x, y, out);
    }

    void mul(vector<uint64_t>& x, uint64_t y, vector<uint64_t>& c);
    void mul(vector<uint64_t>& x, vector<uint64_t>& y, vector<uint64_t>& out);
    void matmul(vector<vector<uint64_t>>& x, vector<vector<uint64_t>>& y,
                vector<vector<uint64_t>>& out);

    void extend(vector<uint64_t>& x, int x_ell, vector<uint64_t>& out, int out_ell);

    void B2A(BoolArray& x, vector<uint64_t>& out);

    void MSB(vector<uint64_t>& x, BoolArray& out);

    void multiplexer(BoolArray& cond, vector<uint64_t>& x, vector<uint64_t>& ret);

    void truncate_reduce(vector<uint64_t>& x, int x_ell, int s, vector<uint64_t>& ret, uint8_t *msb_x=nullptr);

    void scale_up(vector<uint64_t>& x, int x_s, int ell, int s, vector<uint64_t>& ret);

    void reduce(vector<uint64_t>& x, int x_ell, vector<uint64_t>& out, int out_ell);

    void LSB(vector<uint64_t>& x, BoolArray& out);

    void digit_decomposition(vector<uint64_t>& x, int digit_size, vector<vector<uint64_t>>& ret,
                             vector<std::pair<int, int>>& digit_ell_scale);
};