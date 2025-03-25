#ifndef vihsdeioujvosld
#define vihsdeioujvosld

#include "config.h"
#include "logistic-config.h"
#include "ss.h"

using namespace sci;
class Logistic {
    void if_else(BoolArray& cond, vector<uint64_t>& x, vector<uint64_t>& y, vector<uint64_t>& ret);

    void LUT(const vector<uint64_t>& spec_vec, vector<uint64_t>& x, bool signed_, int l_out,
             int s_out, int l_in, vector<uint64_t> out);

    void exp(vector<uint64_t>& in, vector<uint64_t>& out, int s_y);

    void EQ(vector<uint64_t>& x, vector<uint64_t>& y, BoolArray& ret);

    void EQ(vector<uint64_t>& x, uint64_t y, BoolArray& ret);

    void div(vector<uint64_t>& nm, vector<uint64_t>& dn, vector<uint64_t>& out, int l_out, int s_out);

    void sigmoid(vector<uint64_t>& in, vector<uint64_t>& out);

public:
    int party;
    vector<vector<uint64_t>> w;
    IOPack* iopack;
    OTPack* otpack;
    SS_op* ss_op;

    Logistic(int party, size_t size);
    ~Logistic();

    void forward(vector<vector<uint64_t>>& input, vector<vector<uint64_t>>& output);
};

#endif