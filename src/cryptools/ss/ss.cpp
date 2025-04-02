#include "ss.h"
#include <cassert>
#include <chrono>
#include <cstring>

SS_op::SS_op(int party, IOPack* iopack, OTPack* otpack) {
    this->party = party;
    this->iopack = iopack;
    this->otpack = otpack;
    this->aux = new AuxProtocols(party, iopack, otpack);
    // this->eq = new Equality(party, iopack, otpack);
    // this->mill_eq = new MillionaireWithEquality(party, iopack, otpack);
    this->xt = new XTProtocol(party, iopack, otpack);
    this->trunc = new Truncation(party, iopack, otpack);
    this->mult = new LinearOT(party, iopack, otpack);
    this->bool_op = new BoolOp(party, iopack, otpack);
}

SS_op::~SS_op() {
    delete aux;
    // delete eq;
    // delete mill_eq;
    delete xt;
    delete trunc;
    delete mult;
    delete bool_op;
}

void SS_op::add(vector<uint64_t>& x, vector<uint64_t>& y, vector<uint64_t>& out) {
    auto size = x.size();
    assert(size == y.size() && size == out.size());

    uint64_t ell_mask_ = (1ULL << (ELL)) - 1;
    for (auto i = 0; i < size; i++) {
        out[i] = (x[i] + y[i]) & ell_mask_;
    }
}

void SS_op::add(vector<uint64_t>& x, uint64_t y, vector<uint64_t>& out) {
    auto size = x.size();
    assert(size == out.size());

    uint64_t ell_mask_ = (1ULL << (ELL)) - 1;
    for (auto i = 0; i < size; i++) {
        out[i] = (x[i] + (y & ell_mask_)) & ell_mask_;
    }
}

void SS_op::mul(vector<uint64_t>& x, vector<uint64_t>& y, vector<uint64_t>& out) {
    auto dim = x.size();
    assert(dim == x.size() && dim == out.size());

    int32_t bwA = 21, bwB = 21, bwC = bwA + bwB;

    mult->hadamard_product(dim, x.data(), y.data(), out.data(), bwA, bwB, bwC);
}

void SS_op::mul(vector<uint64_t>& x, uint64_t y, vector<uint64_t>& out) {
    auto size = x.size();
    assert(size == out.size());

    uint64_t ell_mask_ = (1ULL << (ELL)) - 1;
    for (auto i = 0; i < size; i++) {
        out[i] = (x[i] * y) & ell_mask_;
    }
}

void SS_op::matmul(vector<vector<uint64_t>>& x, vector<vector<uint64_t>>& y,
                   vector<vector<uint64_t>>& out) {
    auto dim1 = x.size(), dim2 = y.size(), dim3 = y[0].size();
    assert(x[0].size() == dim2);
    assert(dim1 = out.size() && dim3 == out[0].size());

    uint64_t* inA = new uint64_t[dim1 * dim2];
    uint64_t* inB = new uint64_t[dim2 * dim3];
    uint64_t* outC = new uint64_t[dim1 * dim3];
    int32_t bwA = 21, bwB = 21, bwC = bwA + bwB;

    for (auto i = 0; i < dim1; i++) {
        memcpy(inA + i * dim2, x[i].data(), dim2 * sizeof(uint64_t));
    }

    for (auto i = 0; i < dim2; i++) {
        memcpy(inB + i * dim3, y[i].data(), dim3 * sizeof(uint64_t));
    }

    mult->matrix_multiplication(dim1, dim2, dim3, inA, inB, outC, bwA, bwB, bwC);

    for (auto i = 0; i < dim1; i++) {
        memcpy(out[i].data(), outC + i * dim3, dim3 * sizeof(uint64_t));
    }

    delete[] inA;
    delete[] inB;
    delete[] outC;
}

void SS_op::extend(vector<uint64_t>& x, int x_ell, vector<uint64_t>& out, int out_ell) {
    auto size = x.size();
    assert(size == out.size());

    xt->s_extend(size, x.data(), out.data(), x_ell, out_ell);
}

void SS_op::B2A(BoolArray& x, vector<uint64_t>& out) {
    auto size = x.size;
    assert(size == out.size());

    aux->B2A(x.data, out.data(), x.size, ELL);
}

void SS_op::MSB(vector<uint64_t>& x, BoolArray& out) {
    auto size = x.size();
    assert(size == out.size);

    aux->MSB(x.data(), out.data, x.size(), ELL);
}

void SS_op::multiplexer(BoolArray& cond, vector<uint64_t>& x, vector<uint64_t>& ret) {
    assert(cond.size == x.size() && cond.size == ret.size());
    aux->multiplexer(cond.data, x.data(), ret.data(), cond.size, ELL, ELL);
}

void SS_op::truncate_reduce(vector<uint64_t>& x, int x_ell, int s, vector<uint64_t>& ret,
                            uint8_t* msb_x) {
    auto size = x.size();
    assert(size == ret.size());
    if (msb_x != nullptr) {
        aux->B2A(msb_x, ret.data(), size, x_ell - s);
        uint64_t ret_mask = (1ULL << (x_ell - s)) - 1;
        for (int i = 0; i < size; i++) {
            ret[i] = (ret[i] + (x[i] >> s)) & ret_mask;
        }
    } else {
        trunc->truncate_and_reduce(size, x.data(), ret.data(), s, x_ell);
    }
}

void SS_op::scale_up(vector<uint64_t>& x, int x_s, int ell, int s, vector<uint64_t>& ret) {
    assert(s >= x_s);
    auto size = x.size();
    assert(size == ret.size());

    uint64_t ell_mask_ = ((ell == 64) ? -1 : (1ULL << (ell)) - 1);
    for (auto i = 0; i < size; i++) {
        ret[i] = (x[i] << (s - x_s)) & ell_mask_;
    }
}

void SS_op::reduce(vector<uint64_t>& x, int x_ell, vector<uint64_t>& out, int out_ell) {
    auto size = x.size();
    assert(size == out.size());
    uint64_t ell_mask_ = ((out_ell == 64) ? -1 : (1ULL << (out_ell)) - 1);
    for (int i = 0; i < size; i++) {
        out[i] = x[i] & ell_mask_;
    }
}

void SS_op::LSB(vector<uint64_t>& x, BoolArray& out) {
    auto size = x.size();
    assert(size == out.size);
    for (int i = 0; i < size; i++) {
        out.data[i] = x[i] & 1;
    }
}

void SS_op::digit_decomposition(vector<uint64_t>& x, int digit_size, vector<vector<uint64_t>>& ret,
                                vector<std::pair<int, int>>& digit_ell_scale) {
    auto size = x.size();
    assert(digit_size <= 8);
    int num_digits = ceil(ELL / double(digit_size));
    vector<vector<uint64_t>> digits(num_digits);
    for (int i = 0; i < num_digits; i++) {
        int digit_ell = (i == (num_digits - 1) ? ELL - i * digit_size : digit_size);
        int digit_s = SCALE - i * digit_size;
        digits[i] = vector<uint64_t>(size); // FixArray(party, size, false, digit_ell, digit_s);
        digit_ell_scale[i] = std::make_pair(digit_ell, digit_s);
    }
    uint64_t* digits_data = new uint64_t[num_digits * size];
    aux->digit_decomposition_sci(size, x.data(), digits_data, ELL, digit_size);
    for (int i = 0; i < num_digits; i++) {
        memcpy(ret[i].data(), digits_data + i * size, size * sizeof(uint64_t));
    }
}