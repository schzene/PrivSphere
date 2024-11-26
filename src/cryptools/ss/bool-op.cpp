#include "bool-op.h"

using namespace std;
using namespace nisl;

BoolArray BoolArray::subset(int i, int j)
{
    assert(i >= 0 && j <= size && i < j);
    int sz = j - i;
    BoolArray ret(this->party, sz);
    memcpy(ret.data, this->data + i, sz * sizeof(uint8_t));
    return ret;
}

std::ostream &operator<<(std::ostream &os, BoolArray &other)
{
    assert(other.party == PUBLIC);
    os << "[";
    for (int i = 0; i < other.size; i++)
    {
        os << int(other.data[i]) << "\t";
    }
    os << "]";
    return os;
}

BoolArray BoolOp::input(int party_, int sz, uint8_t *data_)
{
    BoolArray ret((party_ == PUBLIC ? party_ : this->party), sz);
    if ((this->party == party_) || (party_ == PUBLIC))
    {
        memcpy(ret.data, data_, sz * sizeof(uint8_t));
        for (int i = 0; i < sz; i++)
        {
            ret.data[i] &= 1;
        }
    }
    else
    {
        memset(ret.data, 0, sz * sizeof(uint8_t));
    }
    return ret;
}

BoolArray BoolOp::input(int party_, int sz, uint8_t data_)
{
    BoolArray ret((party_ == PUBLIC ? party_ : this->party), sz);
    if ((this->party == party_) || (party_ == PUBLIC))
    {
        memset(ret.data, (data_ & 1), sz * sizeof(uint8_t));
    }
    else
    {
        memset(ret.data, 0, sz * sizeof(uint8_t));
    }
    return ret;
}

BoolArray BoolOp::output(int party_, const BoolArray &x)
{
    if (x.party == PUBLIC)
    {
        return x;
    }
    int sz = x.size;
    int ret_party = (party_ == PUBLIC || party_ == x.party ? PUBLIC : x.party);
    BoolArray ret(ret_party, sz);
#pragma omp parallel num_threads(2)
    {
        if (omp_get_thread_num() == 1 && party_ != BOB)
        {
            if (party == ALICE)
            {
                iopack->io_rev->recv_data(ret.data, sz * sizeof(uint8_t));
            }
            else
            { // party == nisl::BOB
                iopack->io_rev->send_data(x.data, sz * sizeof(uint8_t));
            }
        }
        else if (omp_get_thread_num() == 0 && party_ != ALICE)
        {
            if (party == ALICE)
            {
                iopack->io->send_data(x.data, sz * sizeof(uint8_t));
            }
            else
            { // party == nisl::BOB
                iopack->io->recv_data(ret.data, sz * sizeof(uint8_t));
            }
        }
    }
    for (int i = 0; i < sz; i++)
    {
        ret.data[i] = ret.data[i] ^ x.data[i];
    }
    return ret;
}

BoolArray BoolOp::if_else(const BoolArray &cond, const BoolArray &x,
                          const BoolArray &y)
{
    assert(cond.party != PUBLIC);
    assert(cond.size == x.size && cond.size == y.size);
    BoolArray x_xor_y = this->XOR(x, y);
    BoolArray ret = this->AND(cond, x_xor_y);
    return this->XOR(ret, y);
}

BoolArray BoolOp::if_else(const BoolArray &cond, const BoolArray &x,
                          uint8_t y)
{
    assert(cond.party != PUBLIC);
    assert(cond.size == x.size);
    BoolArray bool_y = this->input(PUBLIC, x.size, y);
    return this->if_else(cond, x, bool_y);
}

BoolArray BoolOp::if_else(const BoolArray &cond, uint8_t x,
                          const BoolArray &y)
{
    assert(cond.party != PUBLIC);
    assert(cond.size == y.size);
    BoolArray bool_x = this->input(PUBLIC, y.size, x);
    return this->if_else(cond, bool_x, y);
}

BoolArray BoolOp::NOT(const BoolArray &x)
{
    BoolArray ret(x.party, x.size);
    for (int i = 0; i < x.size; i++)
    {
        ret.data[i] = x.data[i] ^ ((x.party != BOB) ? 1 : 0);
    }
    return ret;
}

BoolArray BoolOp::XOR(const BoolArray &x, const BoolArray &y)
{
    assert(x.size == y.size);
    bool x_cond, y_cond;
    int party_;
    if (x.party == PUBLIC && y.party == PUBLIC)
    {
        x_cond = false;
        y_cond = false;
        party_ = PUBLIC;
    }
    else
    {
        x_cond = (x.party == PUBLIC) && (this->party == BOB);
        y_cond = (y.party == PUBLIC) && (this->party == BOB);
        party_ = this->party;
    }
    BoolArray ret(party_, x.size);
    for (int i = 0; i < x.size; i++)
    {
        ret.data[i] = (x_cond ? 0 : x.data[i]) ^ (y_cond ? 0 : y.data[i]);
    }
    return ret;
}

BoolArray BoolOp::AND(const BoolArray &x, const BoolArray &y)
{
    assert(x.party != PUBLIC || y.party != PUBLIC);
    assert(x.size == y.size);
    BoolArray ret(this->party, x.size);
    if (x.party == PUBLIC || y.party == PUBLIC)
    {
        for (int i = 0; i < x.size; i++)
        {
            ret.data[i] = x.data[i] & y.data[i];
        }
    }
    else
    {
        aux->AND(x.data, y.data, ret.data, x.size);
    }
    return ret;
}

BoolArray BoolOp::OR(const BoolArray &x, const BoolArray &y)
{
    assert(x.party != PUBLIC || y.party != PUBLIC);
    assert(x.size == y.size);
    BoolArray ret(this->party, x.size);
    BoolArray neg_x = this->NOT(x);
    BoolArray neg_y = this->NOT(y);
    return this->NOT(this->AND(neg_x, neg_y));
}