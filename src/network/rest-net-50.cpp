#include "rest-net-50.h"

RestNet50Block::RestNet50Block(unsigned int in_channels, unsigned int out_channels) {
    conv1 = new Convolution(in_channels, out_channels, 1, 1);
    bn1 = new LayerNorm(out_channels);
    relu1 = new ReLU();
    conv2 = new Convolution(out_channels, out_channels, 3, 1, 1);
    bn2 = new LayerNorm(out_channels);
    relu2 = new ReLU();
    conv3 = new Convolution(out_channels, out_channels * 4, 1, 1);
    bn3 = new LayerNorm(out_channels * 4);
}

RestNet50Block::~RestNet50Block() {
    delete conv1;
    delete bn1;
    delete relu1;
    delete conv2;
    delete bn2;
    delete relu2;
    delete conv3;
    delete bn3;
}

void RestNet50Block::forward(const vector<vector<vector<uint64_t>>> &input, vector<vector<vector<uint64_t>>> &output) {
    conv1->forward(input, output);
    bn1->forward(output, output);
    relu1->forward(output, output);
    conv2->forward(output, output);
    bn2->forward(output, output);
    relu2->forward(output, output);
    conv3->forward(output, output);
    bn3->forward(output, output);
}