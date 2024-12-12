#include "simplenet-config.h"

class SimpleNetBlock {
    unsigned int party;

    vector<vector<vector<uint64_t>>> w;
    vector<vector<uint64_t>> b;

    Linear* linear;
    GeLU* gelu;

public:
    SimpleNetBlock(unsigned int party, size_t num_feature, size_t comm_dim, size_t output_dim);
    ~SimpleNetBlock();

    void forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output);
};

class SimpleNet {
    SimpleNetBlock *block1, *block2, *block3;

public:
    SimpleNet(unsigned int party, unsigned num_feature, unsigned comm_dim, unsigned output_dim);
    ~SimpleNet();

    void forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output);
};