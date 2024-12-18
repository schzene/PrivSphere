#include "simplenet-config.h"

class SimpleNetBlock {
    unsigned int party;

    Data w;
    vector<vector<uint64_t>> b;

    Linear* linear;
    GeLU* gelu;

public:
    SimpleNetBlock(unsigned int party, NetIO* io, size_t num_feature, size_t comm_dim, size_t output_dim);
    ~SimpleNetBlock();

    void forward(const Data& input, Data& output);
};

class SimpleNet {
    SimpleNetBlock *block1, *block2, *block3;

public:
    SimpleNet(unsigned int party, NetIO* io, unsigned num_feature, unsigned comm_dim, unsigned output_dim);
    ~SimpleNet();

    void forward(const Data& input, Data& output);
};