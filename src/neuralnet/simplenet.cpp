#include "simplenet.h"
#include "config.h"
#include "neuralnet/simplenet-config.h"

SimpleNetBlock::SimpleNetBlock(unsigned int _party, size_t num_feature, size_t comm_dim, size_t output_dim)
    : party(_party) {
    load_data(w, num_feature, comm_dim, output_dim);
    load_data(b, num_feature, output_dim);

    linear = new Linear(party, nullptr);
    gelu   = new GeLU(party, nullptr);
}

SimpleNetBlock::~SimpleNetBlock() {
    delete linear;
    delete gelu;
}

void SimpleNetBlock::forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output) {
    Linear::Type i_temp, w_temp, o_temp;
    convert(party, Type::HE, linear, input, i_temp);
    convert(party, Type::HE, linear, w, w_temp);
    linear->fc(i_temp, w_temp, o_temp);

    GeLU::Type g_temp;
    convert(party, linear, gelu, o_temp, g_temp);
    gelu->gelu(g_temp, g_temp);

    convert(party, gelu, Type::HE, g_temp, output);
}

SimpleNet::SimpleNet(unsigned int party, unsigned num_feature, unsigned comm_dim, unsigned output_dim) {
    block1 = new SimpleNetBlock(party, num_feature, comm_dim, comm_dim);
    block2 = new SimpleNetBlock(party, num_feature, comm_dim, comm_dim);
    block3 = new SimpleNetBlock(party, num_feature, comm_dim, output_dim);
}

SimpleNet::~SimpleNet() {
    delete block1;
    delete block2;
    delete block3;
}

void SimpleNet::forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output) {
    vector<vector<vector<uint64_t>>> temp;
    block1->forward(input, temp);
    block2->forward(temp, temp);
    block3->forward(temp, output);
}