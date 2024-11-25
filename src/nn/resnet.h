#pragma once
#ifndef PRIVSPHERE_RESNET_H__
#define PRIVSPHERE_RESNET_H__

#include "resnet-config.h"

class ResNetBlock {
    Convolution* conv1;
    LayerNorm* bn1;
    ReLU* relu1;
    Convolution* conv2;
    LayerNorm* bn2;
    ReLU* relu2;
    Convolution* conv3;
    LayerNorm* bn3;

public:
    ResNetBlock(unsigned int in_channels, unsigned int out_channels);
    ~ResNetBlock();
    void forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output);
};

class ResNet {};

#endif