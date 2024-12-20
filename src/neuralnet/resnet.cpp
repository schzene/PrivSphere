#include "resnet.h"

#include <cassert>

ResNetBlock::ResNetBlock(unsigned int _party, unsigned int _n, unsigned int _in_channels, unsigned int _out_channels,
                         unsigned int _stride)
    : party(_party), n(_n), in_channels(_in_channels), out_channels(_out_channels), stride(_stride) {
    conv1 = new Convolution(party, nullptr, 0);
    conv2 = new Convolution(party, nullptr, 0);
    bn    = new BatchNorm(party, nullptr, 0);
    relu  = new ReLU(party);
}

ResNetBlock::~ResNetBlock() {
    delete conv1;
    delete conv2;
    delete bn;
    delete relu;
}

void ResNetBlock::forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output) {
    unsigned int in_channels = input.size(), width = input[0].size(), height = input[0][0].size();

    unsigned int out1_channels = k1.size();
    vector<vector<vector<uint64_t>>> tmp1(out1_channels,
                                          vector<vector<uint64_t>>(width - 2, vector<uint64_t>(height - 2)));
    vector<vector<vector<uint64_t>>> out1(out1_channels, vector<vector<uint64_t>>(width, vector<uint64_t>(height)));
    conv1->conv2d(input, k1, stride, tmp1);
    for (unsigned int i = 0; i < out1_channels; i++) {
        for (unsigned int j = 0; j < width - 2; j++) {
            for (unsigned int k = 0; k < height - 2; k++) {
                out1[i][j + 1][k + 1] = tmp1[i][j][k];
            }
        }
    }
    for (unsigned int i = 0; i < out1_channels; i++) {
        for (unsigned int j = 0; j < width; j++) {
            for (unsigned int k = 0; k < height; k++) {
                out1[i][j][k] += b1[i][j];
            }
        }
    }

    uint64_t scale = 1ULL << 13;
    bn->bn(out1, out1, scale);
    // relu->forward(out1, out1);

    unsigned int out2_channels = k2.size();
    vector<vector<vector<uint64_t>>> tmp2(out2_channels,
                                          vector<vector<uint64_t>>(width - 2, vector<uint64_t>(height - 2)));
    vector<vector<vector<uint64_t>>> out2(out2_channels, vector<vector<uint64_t>>(width, vector<uint64_t>(height)));
    conv2->conv2d(out1, k2, stride, tmp2);
    for (unsigned int i = 0; i < out2_channels; i++) {
        for (unsigned int j = 0; j < width - 2; j++) {
            for (unsigned int k = 0; k < height - 2; k++) {
                out2[i][j + 1][k + 1] = tmp2[i][j][k];
            }
        }
    }
    for (unsigned int i = 0; i < out2_channels; i++) {
        for (unsigned int j = 0; j < width; j++) {
            for (unsigned int k = 0; k < height; k++) {
                out2[i][j][k] += b2[i][j];
            }
        }
    }
    bn->bn(out2, out2, scale);

    if (stride != 1 || in_channels != out_channels) {
        assert(out1_channels == out2_channels);
        conv2->conv2d(input, k, stride, out1);
        for (unsigned int i = 0; i < out1_channels; i++) {
            for (unsigned int j = 0; j < width; j++) {
                for (unsigned int k = 0; k < height; k++) {
                    out1[i][j][k] += b[i][j];
                }
            }
        }
        bn->bn(out1, out1, scale);
        for (unsigned int i = 0; i < out2_channels; i++) {
            for (unsigned int j = 0; j < width; j++) {
                for (unsigned int k = 0; k < height; k++) {
                    out2[i][j][k] += out1[i][j][k];
                }
            }
        }
    }

    unsigned int out3_channels = k1.size();
    vector<vector<vector<uint64_t>>> tmp3(out3_channels,
                                          vector<vector<uint64_t>>(width - 2, vector<uint64_t>(height - 2)));
    vector<vector<vector<uint64_t>>> out3(out3_channels, vector<vector<uint64_t>>(width, vector<uint64_t>(height)));
    conv2->conv2d(out2, k3, stride, tmp3);
    for (unsigned int i = 0; i < out3_channels; i++) {
        for (unsigned int j = 0; j < width - 2; j++) {
            for (unsigned int k = 0; k < height - 2; k++) {
                out3[i][j + 1][k + 1] = tmp3[i][j][k];
            }
        }
    }
    for (unsigned int i = 0; i < out3_channels; i++) {
        for (unsigned int j = 0; j < width; j++) {
            for (unsigned int k = 0; k < height; k++) {
                out3[i][j][k] += b3[i][j];
            }
        }
    }

    bn->bn(out3, out3, scale);
    // relu->forward(out3, out3);

    unsigned int out4_channels = k1.size();
    vector<vector<vector<uint64_t>>> tmp4(out4_channels,
                                          vector<vector<uint64_t>>(width - 2, vector<uint64_t>(height - 2)));
    output = vector<vector<vector<uint64_t>>>(out4_channels, vector<vector<uint64_t>>(width, vector<uint64_t>(height)));
    conv2->conv2d(out3, k4, stride, tmp4);
    for (unsigned int i = 0; i < out4_channels; i++) {
        for (unsigned int j = 0; j < width - 2; j++) {
            for (unsigned int k = 0; k < height - 2; k++) {
                output[i][j + 1][k + 1] = tmp4[i][j][k];
            }
        }
    }
    for (unsigned int i = 0; i < out4_channels; i++) {
        for (unsigned int j = 0; j < width; j++) {
            for (unsigned int k = 0; k < height; k++) {
                output[i][j][k] += b4[i][j];
            }
        }
    }

    bn->bn(output, output, scale);
}

ResNet::ResNet() {
    conv    = new Convolution(party, nullptr, 0);
    bn      = new BatchNorm(party, nullptr, 0);
    relu    = new ReLU(party);
    // maxpool = new MaxPool(3, 2);
    layer1  = new ResNetBlock(1, 64, 64, 1);
    layer2  = new ResNetBlock(2, 64, 128, 2);
    layer3  = new ResNetBlock(3, 128, 256, 2);
    layer4  = new ResNetBlock(4, 256, 512, 2);
    fc      = new Linear(party, nullptr, 0);
}

ResNet::~ResNet() {
    delete conv;
    delete bn;
    delete relu;
    // delete maxpool;
    delete layer1;
    delete layer2;
    delete layer3;
    delete layer4;
    delete fc;
}

void ResNet::forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output) {
    unsigned int out_channels = k.size(), width = input[0].size(), height = input[0][0].size();
    vector<vector<vector<uint64_t>>> tmp1(out_channels,
                                          vector<vector<uint64_t>>(width - 6, vector<uint64_t>(height - 6)));
    vector<vector<vector<uint64_t>>> out1(out_channels, vector<vector<uint64_t>>(width, vector<uint64_t>(height)));
    conv->conv2d(input, k, 1, tmp1);
    for (unsigned int i = 0; i < out_channels; i++) {
        for (unsigned int j = 0; j < width - 6; j++) {
            for (unsigned int k = 0; k < height - 6; k++) {
                out1[i][j + 3][k + 3] = tmp1[i][j][k];
            }
        }
    }
    for (unsigned int i = 0; i < out_channels; i++) {
        for (unsigned int j = 0; j < width; j++) {
            for (unsigned int k = 0; k < height; k++) {
                out1[i][j][k] += b[i][j];
            }
        }
    }

    uint64_t scale = 1ULL<<13;
    bn->bn(out1, out1, scale);
    // relu->forward(out1, out1);

    vector<vector<vector<uint64_t>>> tmp2(out_channels,
                                          vector<vector<uint64_t>>(width - 2, vector<uint64_t>(height - 2)));
    vector<vector<vector<uint64_t>>> out2(out_channels, vector<vector<uint64_t>>(width, vector<uint64_t>(height)));
    // maxpool->forward(out1, tmp2);
    for (unsigned int i = 0; i < out_channels; i++) {
        for (unsigned int j = 0; j < width - 2; j++) {
            for (unsigned int k = 0; k < height - 2; k++) {
                out2[i][j + 1][k + 1] = tmp2[i][j][k];
            }
        }
    }

    layer1->forward(out2, output);
    layer2->forward(output, output);
    layer3->forward(output, output);
    layer4->forward(output, output);

    fc->fc(output, w, output);
    for (unsigned int i = 0; i < out_channels; i++) {
        for (unsigned int j = 0; j < width; j++) {
            output[i][j][0] += b_w[i][j];
        }
    }
}