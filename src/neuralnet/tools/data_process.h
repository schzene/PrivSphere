#pragma once
#ifndef PRIVSPHERE_NETDATATOOL_H__
#define PRIVSPHERE_NETDATATOOL_H__

#include <cstdint>
#include <vector>

#include "config.h"
#include "nexus-op.h"

/**
 * @brief Convert input 'i' of type 's' to output 'o' of type 't'
 *
 * @param party Participants
 * @param s input type
 * @param t output type
 * @param i Input
 * @param o Output
 */
void convert(unsigned party, const MPCType s, const MPCType t, const Data& i, Data& o);

/**
 * @brief Convert input 'i' of operator type 's' to output 'o' of operator type 't'
 *
 * @param party Participants
 * @param s Operator input type
 * @param t Operator output type
 * @param i Input
 * @param o Output
 */
inline void convert(unsigned party, const OP* s, const OP* t, const Data& i, Data& o) {
    convert(party, s->type, t->type, i, o);
}

/**
 * @brief Convert input 'i' of operator type 's' to output 'o' of type 't'
 *
 * @param party Participants
 * @param s Operator input type
 * @param t Output type
 * @param i Input
 * @param o Output
 */
inline void convert(unsigned party, const MPCType s, const OP* t, const Data& i, Data& o) {
    convert(party, s, t->type, i, o);
}

/**
 * @brief Convert input 'i' of type 's' to output 'o' of operator type 't'
 *
 * @param party Participants
 * @param s Input type
 * @param t Operator output type
 * @param i Input
 * @param o Output
 */
inline void convert(unsigned party, const OP* s, const MPCType t, const Data& i, Data& o) {
    convert(party, s->type, t, i, o);
}

void load_data(vector<vector<vector<uint64_t>>> A, size_t dim1, size_t dim2, size_t dim3);
void load_data(vector<vector<uint64_t>> B, size_t dim1, size_t dim2);
// using std::vector;

// class Linear {
// public:
//     Linear() {}
//     void forward(const vector<vector<vector<uint64_t>>>& input, const vector<vector<vector<uint64_t>>>& weight,
//                  vector<vector<vector<uint64_t>>>& output) {}
// };

// class Convolution {
// protected:
//     unsigned int stride;

// public:
//     Convolution() : stride(1) {}
//     Convolution(unsigned int _stride) : stride(_stride) {}

//     void forward(const vector<vector<vector<uint64_t>>>& input, const vector<vector<vector<vector<uint64_t>>>>& kernel,
//                  vector<vector<vector<uint64_t>>>& output) {}
// };

// class MaxPool {
// protected:
//     unsigned int kernel_size, stride;

// public:
//     MaxPool(unsigned int _kernel_size) : kernel_size(_kernel_size), stride(1) {}
//     MaxPool(unsigned int _kernel_size, unsigned int _stride) : kernel_size(_kernel_size), stride(_stride) {}
//     void forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output) {}
// };

// class LayerNorm {
// public:
//     LayerNorm() {}
//     void forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output) {}
// };

// class BatchNorm {
// public:
//     BatchNorm() {}
//     void forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output) {}
// };

// class ReLU {
// public:
//     ReLU() {}
//     void forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output) {}
// };

// class SoftMax {
// public:
//     SoftMax() {}
//     void forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output) {}
// };

// class GeLU {
// public:
//     GeLU() {}
//     void forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output) {}
// };

#endif