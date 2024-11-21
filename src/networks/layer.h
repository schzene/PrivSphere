#ifndef PRIVSPHERE_LAYER_H__
#define PRIVSPHERE_LAYER_H__

#include <vector>
using std::vector;
typedef unsigned long int uint64_t;

class Layer {
public:
    virtual void forward(const vector<vector<vector<uint64_t>>> &input, vector<vector<vector<uint64_t>>> &output) = 0;
};

#endif