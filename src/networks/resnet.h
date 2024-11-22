#include "resnet-config.h"

class RestNet50Block {
    Convolution *conv1;
    LayerNorm *bn1;
    ReLU *relu1;
    Convolution *conv2;
    LayerNorm *bn2;
    ReLU *relu2;
    Convolution *conv3;
    LayerNorm *bn3;

public:
    RestNet50Block(unsigned int in_channels, unsigned int out_channels);
    ~RestNet50Block();
    void forward(const vector<vector<vector<uint64_t>>> &input, vector<vector<vector<uint64_t>>> &output);
};

class RestNet50 {

};