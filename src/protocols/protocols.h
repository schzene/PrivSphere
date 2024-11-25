#pragma once
#ifndef PRIVSPHERE_PROTOCOLS_H__
#define PRIVSPHERE_PROTOCOLS_H__

#include <cstdint>
#include <vector>

using std::vector;

class Linear {
public:
    Linear() {}
    void forward(const vector<vector<vector<uint64_t>>>& input, const vector<vector<vector<uint64_t>>>& weight,
                 vector<vector<vector<uint64_t>>>& output) {}
};

class Convolution {
protected:
    unsigned int stride;

public:
    Convolution() : stride(1) {}

    Convolution(unsigned int _stride) : stride(_stride) {}

    void forward(const vector<vector<vector<uint64_t>>>& input, const vector<vector<vector<vector<uint64_t>>>>& kernel,
                 vector<vector<vector<uint64_t>>>& output) {}
};

class LayerNorm {
public:
    LayerNorm() {}
    void forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output) {}
};

class BatchNorm {
public:
    BatchNorm() {}
    void forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output) {}
};

class ReLU {
public:
    ReLU() {}
    void forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output) {}
};

class SoftMax {
public:
    SoftMax() {}
    void forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output) {}
};

class GeLU {
public:
    GeLU() {}
    void forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output) {}
};

#endif