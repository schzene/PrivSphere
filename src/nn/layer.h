#ifndef PRIVSPHERE_LAYER_H__
#define PRIVSPHERE_LAYER_H__

#include <cstdint>
#include <vector>
using std::vector;

class Layer {
public:
    virtual void forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output) = 0;
};

#endif