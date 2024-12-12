#pragma once
#ifndef PRIVSPHERE_PROTOCOLS_H__
#define PRIVSPHERE_PROTOCOLS_H__

#include <cstdint>
#include <vector>

#include "config.h"
#include "cryptools/he/cheetah-op.h"
#include "cryptools/he/nexus-op.h"

/**
 * @brief Convert input 'i' of operator type 's' to output 'o' of operator type 't'
 *
 * @param party Participants
 * @param s Operator input type
 * @param t Operator output type
 * @param i Input
 * @param o Output
 */
template <class S, class T, class I, class O>
void convert(unsigned party, S s, T t, I& i, O& o) {
    convert(party, s.type, t.type, i, o);
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
template <class T, class I, class O>
void convert(unsigned party, Type s, T t, I& i, O& o) {
    convert(party, s, t.type, i);
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
template <class S, class I, class O>
void convert(unsigned party, S s, Type t, I& i, O& o) {
    convert(party, s.type, t, i);
}


/**
 * @brief Convert input 'i' of type 's' to output 'o' of type 't'
 *
 * @param party Participants
 * @param s input type
 * @param t output type
 * @param i Input
 * @param o Output
 */
template <class I, class O>
void convert(unsigned party, Type s, Type t, I& i, O& o) {
    switch (s) {
        case Type::HE: {
            switch (t) {
                case Type::HE: {
                    return i;
                }
                case Type::SS: {
                    break;
                }
                case Type::NEXUS: {
                    o = vector<vector<vector<double>>>(
                        i.size(), vector<vector<double>>(i[0].size(), vector<double>(i[0][0].size(), 1.0)));
                }
            }
            break;
        }
        case Type::SS: {
            switch (t) {
                case Type::HE: {
                    break;
                }
                case Type::SS: {
                    return i;
                }
                case Type::NEXUS: {
                    break;
                }
            }
            break;
        }
        case Type::NEXUS: {
            switch (t) {
                case Type::HE: {
                    o = vector<vector<vector<uint64_t>>>(
                        i.size(), vector<vector<uint64_t>>(i[0].size(), vector<uint64_t>(i[0][0].size(), 1)));
                }
                case Type::SS: {
                    break;
                }
                case Type::NEXUS: {
                    return i;
                }
            }
            break;
        }
    }
    o = vector<vector<vector<uint64_t>>>(i.size(),
                                         vector<vector<uint64_t>>(i[0].size(), vector<uint64_t>(i[0][0].size(), 1)));
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