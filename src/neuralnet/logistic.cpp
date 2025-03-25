#include "logistic.h"
#include "LinearOT/linear-ot.h"
#include "logistic-config.h"
#include "ss.h"
#include <cstdint>
#include <vector>

void Logistic::if_else(BoolArray& cond, vector<uint64_t>& x, vector<uint64_t>& y,
                       vector<uint64_t>& ret) {
    assert(cond.size == x.size() && cond.size == y.size() && cond.size == ret.size());

    vector<uint64_t> diff(cond.size, 0), neg_y(cond.size, 0);
    mul_op->mul(y, uint64_t(-1), neg_y);
    add_op->add(x, neg_y, diff);
    multiplexer_op->multiplexer(cond, diff, ret);
    add_op->add(ret, y, ret);
}

void Logistic::LUT(const vector<uint64_t>& spec_vec, vector<uint64_t>& x, bool signed_, int l_out,
                   int s_out, int l_in, vector<uint64_t> out) {
    size_t size = x.size();
    assert(size == out.size());
    assert(l_out < 64);
    assert(spec_vec.size() == (1 << l_in));
    if (l_in > 8) {
        assert(l_in <= 14);
        int l_rem = l_in - 8;
        int n = 1 << l_rem;
        vector<uint64_t> x_red(size);
        reduce_op->reduce(x, l_in, x_red, 8);
        vector<vector<uint64_t>> lspec_vec(n);
        for (int i = 0; i < n; i++) {
            lspec_vec[i].resize(1 << 8);
            for (int j = 0; j < (1 << 8); j++) {
                lspec_vec[i][j] = spec_vec[i * (1 << 8) + j];
            }
        }
        vector<vector<uint64_t>> lout(1 << l_rem, vector<uint64_t>(size));
        for (int i = 0; i < (1 << l_rem); i++) {
            LUT(lspec_vec[i], x_red, signed_, l_out, s_out, 8, lout[i]);
        }
        vector<uint64_t> x_hi(size);
        truncate_reduce_op->truncate_reduce(x, l_in, 8, x_hi);
        reduce_op->reduce(x_hi, 8, x_hi, l_rem);
        uint64_t x_mask = (1ULL << (l_rem)) - 1;
        uint64_t LUT_out_mask = (1ULL << n) - 1;
        uint64_t* LUT_out = new uint64_t[size];
        if (party == 1) {
            uint64_t** spec;
            spec = new uint64_t*[size];
            PRG128 prg;
            prg.random_data(LUT_out, size * sizeof(uint64_t));
            for (int i = 0; i < size; i++) {
                spec[i] = new uint64_t[1 << l_rem];
                LUT_out[i] &= LUT_out_mask;
                for (int j = 0; j < (1 << l_rem); j++) {
                    int idx = (x_hi[i] + j) & x_mask;
                    vector<uint8_t> spec_active_interval(n, 0);
                    spec_active_interval[idx] = 1;
                    uint64_t spec_data = 0;
                    uint64_t LUT_out_data = LUT_out[i];
                    for (int k = 0; k < n; k++) {
                        spec_data |= (((spec_active_interval[k] ^ LUT_out_data) & 1) << k);
                        LUT_out_data >>= 1;
                    }
                    spec[i][j] = spec_data;
                }
            }
            ss_op->aux->lookup_table<uint64_t>(spec, nullptr, nullptr, size, l_rem, n);

            for (int i = 0; i < size; i++)
                delete[] spec[i];
            delete[] spec;
        } else {
            ss_op->aux->lookup_table<uint64_t>(nullptr, x_hi.data(), LUT_out, size, l_rem, n);
        }
        uint8_t* v = new uint8_t[size * n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < size; j++) {
                v[i * size + j] = LUT_out[j] & 1;
                LUT_out[j] >>= 1;
            }
        }
        vector<BoolArray> v_bl(n);
        vector<vector<uint64_t>> lout_v(n, vector<uint64_t>(size));
        vector<uint64_t> zero(size, 0ULL);
        for (int i = 0; i < n; i++) {
            v_bl[i] = ss_op->bool_op->input(this->party, size, v + i * size);
            if_else(v_bl[i], lout[i], zero, lout_v[i]);
        }
        memset(out.data(), 0, size * sizeof(uint64_t));
        for (int i = 0; i < n; i++) {
            add_op->add(out, lout_v[i], out);
        }
        delete[] v;
        delete[] LUT_out;
        return;
    }
    assert(l_in <= 8);

    uint64_t x_mask = (1ULL << (l_in)) - 1;
    uint64_t ret_mask = (1ULL << (l_out)) - 1;
    if (party == 1) {
        uint64_t** spec;
        spec = new uint64_t*[size];
        PRG128 prg;
        prg.random_data(out.data(), size * sizeof(uint64_t));
        for (int i = 0; i < size; i++) {
            spec[i] = new uint64_t[spec_vec.size()];
            out[i] &= ret_mask;
            for (int j = 0; j < spec_vec.size(); j++) {
                int idx = (x[i] + j) & x_mask;
                spec[i][j] = (spec_vec[idx] - out[i]) & ret_mask;
            }
        }
        ss_op->aux->lookup_table<uint64_t>(spec, nullptr, nullptr, size, l_in, l_out);

        for (int i = 0; i < size; i++)
            delete[] spec[i];
        delete[] spec;
    } else {
        ss_op->aux->lookup_table<uint64_t>(nullptr, x.data(), out.data(), size, l_in, l_out);
    }
}

void Logistic::exp(vector<uint64_t>& in, vector<uint64_t>& out, int s_y) {
    int l_y = s_y + 2;
    int digit_size = 8;
    auto size = in.size();
    assert(size == out.size());

    vector<uint64_t> pos_x(size);
    mul_op->mul(in, -1, pos_x);

    int num_digits = ceil(ELL / double(digit_size));
    vector<vector<uint64_t>> digits(num_digits, vector<uint64_t>(size));
    vector<std::pair<int, int>> digit_ell_scale(num_digits);
    digit_decomposition_op->digit_decomposition(pos_x, digit_size, digits, digit_ell_scale);

    vector<vector<uint64_t>> digits_exp(num_digits, vector<uint64_t>(size, 0));
    for (int i = 0; i < num_digits; i++) {
        vector<uint64_t> spec(1 << digit_ell_scale[i].first);
        for (int j = 0; j < (1 << digit_ell_scale[i].first); j++) {
            spec[j] = std::exp(-1.0 * (j / pow(2.0, digit_ell_scale[i].second))) * (1ULL << s_y);
        }
        LUT(spec, digits[i], true, s_y + 2, s_y, digit_ell_scale[i].first, digits_exp[i]);
    }

    BoolArray all_0 = ss_op->bool_op->input(sci::ALICE, size, uint8_t(0));
    for (int i = 1; i < num_digits; i *= 2) {
        for (int j = 0; j < num_digits && j + i < num_digits; j += 2 * i) {
            ss_op->mult->hadamard_product(digits_exp[j].size(), digits_exp[j].data(),
                                          digits_exp[j + i].data(), digits_exp[j].data(), s_y + 2,
                                          s_y + 2, 2 * s_y + 2, true, true, MultMode::None,
                                          all_0.data, all_0.data);
            truncate_reduce_op->truncate_reduce(digits_exp[j], 2 * s_y + 2, s_y, digits_exp[j]);
        }
    }

    ss_op->xt->s_extend(digits_exp[0].size(), digits_exp[0].data(), out.data(), s_y, l_y,
                        all_0.data);
}

void Logistic::EQ(vector<uint64_t>& x, vector<uint64_t>& y, BoolArray& ret) {
    auto size = x.size();
    assert(size == y.size() && size == ret.size);

    vector<uint64_t> diff(size);
    add_op->add(x, -1, diff);
    add_op->add(diff, y, diff);
    msb_op->MSB(diff, ret);
}

void Logistic::EQ(vector<uint64_t>& x, uint64_t y, BoolArray& ret) {
    auto size = x.size();
    assert(size == ret.size);

    vector<uint64_t> diff(size);
    add_op->add(x, -1, diff);
    add_op->add(diff, y, diff);
    msb_op->MSB(diff, ret);
}

// A0 \in (1/4, 1)
inline uint64_t recp_lookup_c0(uint64_t index, int m) {
    uint64_t k = 1ULL << m;
    double p = 1 + (double(index) / double(k));
    double A1 = 1.0 / (p * (p + 1.0 / double(k)));
    int32_t scale = m + 3;
    uint64_t mask = (1ULL << scale) - 1;
    uint64_t val = uint64_t(A1 * (1ULL << scale)) & mask;
    return val;
}

// A1 \in (1/2, 1)
inline uint64_t recp_lookup_c1(uint64_t index, int m) {
    uint64_t k = 1ULL << m;
    double p = 1 + (double(index) / double(k));
    double z = (p * (p + (1.0 / double(k))));
    double A1 = ((1.0 / double(k * 2)) + sqrt(z)) / z;
    int32_t scale = 2 * m + 2;
    uint64_t mask = (1ULL << scale) - 1;
    uint64_t val = uint64_t(A1 * (1ULL << scale)) & mask;
    return val;
}

// void Logistic::div(vector<uint64_t>& nm, vector<uint64_t>& dn, vector<uint64_t>& out, int l_out,
//                    int s_out) {
//     size_t size = nm.size();
//     assert(size == dn.size());
//     BoolArray all_0 = ss_op->bool_op->input(sci::ALICE, size, uint8_t(0));
//     BoolArray all_1 = ss_op->bool_op->input(sci::ALICE, size, uint8_t(1));

//     vector<uint64_t> nrmlzd_dn(size);
//     vector<uint64_t> adjust(size, uint64_t(0));

//     reduce_op->reduce(dn, ELL, nrmlzd_dn, SCALE + 2);

//     int32_t m, iters;
//     m = (s_out <= 18 ? ceil((s_out - 2) / 2.0) : ceil((ceil(s_out / 2.0) - 2) / 2.0));
//     iters = (s_out <= 18 ? 0 : 1);

//     // reciprocal approximation w
//     vector<uint64_t> eps(size);
//     reduce_op->reduce(nrmlzd_dn, SCALE + 2, eps, SCALE + 2 - m);

//     BoolArray msb_eps = ss_op->bool_op->input(party, size, uint8_t(0));
//     msb_op->MSB(eps, msb_eps);
//     uint8_t* wrap_eps = new uint8_t[size];
//     ss_op->aux->MSB_to_Wrap(eps.data(), msb_eps.data, wrap_eps, size, SCALE + 2 - m);

//     vector<uint64_t> idx(size);
//     reduce_op->reduce(nrmlzd_dn, SCALE + 2, idx, SCALE + 2);
//     truncate_reduce_op->truncate_reduce(idx, SCALE + 2, SCALE + 2 - m, idx, wrap_eps);

//     delete[] wrap_eps;
//     vector<uint64_t> spec_c0(1 << (SCALE + 2 - m));
//     vector<uint64_t> spec_c1(1 << (SCALE + 2 - m));
//     for (int j = 0; j < (1 << (SCALE + 2 - m)); j++) {
//         spec_c0[j] = recp_lookup_c0(j, m);
//         spec_c1[j] = recp_lookup_c1(j, m);
//     }
//     vector<uint64_t> c0(size), c1(size), w(size);
//     LUT(spec_c0, idx, true, m + 4, m + 3, SCALE + 2 - m, c0);
//     LUT(spec_c1, idx, true, 2 * m + 3, 2 * m + 2, SCALE + 2 - m, c1);

//     FixArray w = fix->mul(c0, eps, nrmlzd_dn.s + 4, all_0.data, msb_eps.data);
//     w = fix->sub(fix->scale_up(c1, nrmlzd_dn.s + m + 4, nrmlzd_dn.s + m + 3),
//                  fix->extend(w, nrmlzd_dn.s + m + 4, all_0.data));
//     w = fix->truncate_reduce(w, w.s - s_out);

//     BoolArray msb_nm;
//     uint8_t* msb_nm_data = nullptr;
//     if (nm.signed_) {
//         msb_nm = fix->MSB(nm);
//         msb_nm_data = msb_nm.data;
//     }
//     FixArray a = fix->mul(nm, w, nm.ell + s_out, msb_nm_data, all_0.data);
//     a = fix->truncate_reduce(a, nm.s);
//     if ((nm.ell - nm.s) >= (l_out - s_out)) {
//         a = fix->reduce(a, l_out);
//     } else {
//         a = fix->extend(a, l_out, msb_nm_data);
//     }

//     if (!normalized_dn) {
//         a = fix->mul(a, adjust, l_out + adjust.s, msb_nm_data, all_0.data);
//         a = fix->truncate_reduce(a, adjust.s);
//     }

//     if (iters > 0) {
//         FixArray d = fix->mul(w, nrmlzd_dn, s_out + nrmlzd_dn.s + 2, all_0.data, all_0.data);
//         d = fix->truncate_reduce(d, nrmlzd_dn.s);
//         FixArray e = fix->sub(1ULL << d.s, d);
//         e.signed_ = true;

//         FixArray a_curr, e_curr;
//         FixArray a_prev = a, e_prev = e;
//         for (int i = 0; i < iters - 1; i++) {
//             e_curr = fix->mul(e_prev, e_prev, 2 * s_out + 2, all_0.data, all_0.data);
//             e_curr = fix->truncate_reduce(e_curr, s_out);
//             e_prev = fix->add(e_prev, 1ULL << e_prev.s);
//             a_curr = fix->mul(e_prev, a_prev, l_out + s_out, all_0.data, msb_nm_data);
//             a_curr = fix->truncate_reduce(a_curr, s_out);
//             a_prev = a_curr;
//             e_prev = e_curr;
//         }
//         e_prev = fix->add(e_prev, 1ULL << e_prev.s);
//         FixArray out = fix->mul(e_prev, a_prev, l_out + s_out, all_0.data, msb_nm_data);
//         out = fix->truncate_reduce(out, s_out);
//         return out;
//     } else {
//         return a;
//     }
// }

void Logistic::sigmoid(vector<uint64_t>& in, vector<uint64_t>& out) {
    auto size = in.size();
    assert(size == out.size());

    int s_y = SCALE, l_y = ELL;

    BoolArray msb_x(party, in.size());
    msb_op->MSB(in, msb_x);
    vector<uint64_t> neg_x(size);
    if_else(msb_x, in, neg_x, neg_x);

    vector<uint64_t> exp_neg_x(size);
    exp(neg_x, exp_neg_x, s_y);
    vector<uint64_t> dn(size);
    add_op->add(exp_neg_x, 1ULL << (s_y + 2), dn);

    // if dn.data == 2 * 2^{dn.s}, subtract 1 from dn.data to ensure normalized form of dn
    BoolArray dn_eq_2(party, dn.size());
    EQ(dn, 2ULL << SCALE, dn_eq_2);
    vector<uint64_t> dn_sub1(size);
    add_op->add(dn, uint64_t(-1), dn_sub1);
    if_else(dn_eq_2, dn_sub1, dn, dn);

    //     // setting one_dn as secret-shared as div expects a secret-share numerator
    //     FixArray one_dn = fix->input(ALICE, x.size, 1, true, 2, 0);
    //     FixArray inv_dn = fix->div(one_dn, dn, s_y + 2, s_y, true);

    vector<uint64_t> one_nm(size, 1ULL << (s_y + 2)), nm(size);
    if_else(msb_x, exp_neg_x, one_nm, nm);

    BoolArray all_0 = ss_op->bool_op->input(1, dn.size(), uint8_t(0));
    //     FixArray ret = fix->mul(nm, inv_dn, 2*s_y + 2, all_0.data, all_0.data);
    truncate_reduce_op->truncate_reduce(out, 2 * s_y + 2, s_y, out);
    if (l_y >= s_y + 2) {
        extend_op->extend(out, s_y, out, l_y);
    } else {
        reduce_op->reduce(out, s_y, out, l_y);
    }
}

Logistic::Logistic(int party, size_t size) {
    this->party = party;

    iopack = new IOPack(party, 32000);
    otpack = new OTPack(iopack, party);
    ss_op = new SS_op(party, iopack, otpack);
    w = vector<vector<uint64_t>>(1, vector<uint64_t>(size, 0));
}

Logistic::~Logistic() {
    delete ss_op;
    delete otpack;
    delete iopack;
}

void Logistic::forward(vector<vector<uint64_t>>& input, vector<vector<uint64_t>>& output) {
    assert(input.size() == w[0].size());
    auto out_dim = input[0].size();

    mul_op->matmul(w, input, output);

    sigmoid(output[0], output[0]);
}