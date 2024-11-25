#include "resnet.h"

ResNetBlock::ResNetBlock(unsigned int in_channels, unsigned int out_channels) {
    conv1 = new Convolution();
    bn1   = new LayerNorm();
    relu1 = new ReLU();
    conv2 = new Convolution();
    bn2   = new LayerNorm();
    relu2 = new ReLU();
    conv3 = new Convolution();
    bn3   = new LayerNorm();
}

ResNetBlock::~ResNetBlock() {
    delete conv1;
    delete bn1;
    delete relu1;
    delete conv2;
    delete bn2;
    delete relu2;
    delete conv3;
    delete bn3;
}

void ResNetBlock::forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output) {
    vector<vector<vector<vector<uint64_t>>>> kernel;
    conv1->forward(input, kernel, output);
    bn1->forward(output, output);
    relu1->forward(output, output);
    conv2->forward(output, kernel, output);
    bn2->forward(output, output);
    relu2->forward(output, output);
    conv3->forward(output, kernel, output);
    bn3->forward(output, output);
}