#pragma once
#ifndef PRIVSPHERE_PROTOCOLS_H__
#define PRIVSPHERE_PROTOCOLS_H__

#include <cstdint>
#include <vector>

#include "config.h"
#include "cryptools/he/nexus-op.h"
#include "cryptools/ss/ss.h"

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

void load_data(vector<vector<vector<uint64_t>>>& A, size_t dim1, size_t dim2, size_t dim3);
void load_data(vector<vector<uint64_t>>& B, size_t dim1, size_t dim2);

#endif