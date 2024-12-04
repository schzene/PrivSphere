#pragma once
#ifndef PRIVSPHERE_CHEETAH_H__
#define PRIVSPHERE_CHEETAH_H__

#include <cryptools/he/cheetahtools/cheetah-api.h>

#include <vector>
using std::vector;

namespace cheetah {
void init(int party);
void deinit();

void conv2d(const vector<vector<vector<uint64_t>>>& input, const vector<vector<vector<vector<uint64_t>>>>& kernel,
            size_t stride, vector<vector<vector<uint64_t>>>& output);

void fc(const vector<vector<vector<uint64_t>>>& input, const vector<vector<vector<uint64_t>>>& weight,
        vector<vector<vector<uint64_t>>>& output);

void bn(const vector<vector<vector<uint64_t>>>& input, const vector<vector<vector<uint64_t>>>& scale,
        vector<vector<vector<uint64_t>>>& output);
}  // namespace cheetah

#endif