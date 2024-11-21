#ifndef PRIVSPHERE_PROTOCOLS_H__
#define PRIVSPHERE_PROTOCOLS_H__

#include <cstdint>
#include <vector>
using std::vector;

class Linear {
public:
    Linear() {}
    void forward(const vector<vector<vector<uint64_t>>> &input, const vector<vector<vector<uint64_t>>> &weight, vector<vector<vector<uint64_t>>> &output) {}
};

class Convolution {
protected:
    unsigned int in_channels;
    unsigned int out_channels;
    unsigned int kernel_size;
    unsigned int stride;
    unsigned int padding;

public:
    Convolution() : 
        in_channels(1), 
        out_channels(1), 
        kernel_size(3), 
        stride(1), 
        padding(0) {}

    Convolution(unsigned int _in_channels, unsigned int _out_channels, unsigned int _kernel_size, unsigned int _stride) : 
        in_channels(_in_channels), 
        out_channels(_out_channels), 
        kernel_size(_kernel_size), 
        stride(_stride), 
        padding(0) {}
    
    Convolution(unsigned int _in_channels, unsigned int _out_channels, unsigned int _kernel_size, unsigned int _stride, unsigned int _padding) :
        in_channels(_in_channels),
        out_channels(_out_channels),
        kernel_size(_kernel_size),
        stride(_stride),
        padding(_padding) {}

    void forward(const vector<vector<vector<uint64_t>>> &input, vector<vector<vector<uint64_t>>> &output) {}
};

class LayerNorm {
public:
    LayerNorm() {}
    void forward(const vector<vector<vector<uint64_t>>> &input, vector<vector<vector<uint64_t>>> &output) {}
};


class ReLU {
public:
    ReLU() {}
    void forward(const vector<vector<vector<uint64_t>>> &input, vector<vector<vector<uint64_t>>> &output) {}
};

class SoftMax {
public:
    SoftMax() {}
    void forward(const vector<vector<vector<uint64_t>>> &input, vector<vector<vector<uint64_t>>> &output) {}
};

class GeLU {
public:
    GeLU() {}
    void forward(const vector<vector<vector<uint64_t>>> &input, vector<vector<vector<uint64_t>>> &output) {}
};

#endif