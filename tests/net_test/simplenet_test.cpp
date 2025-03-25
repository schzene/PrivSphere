#include "neuralnet/simplenet.h"
#include <iostream>
#include <vector>
#include <random>
using std::vector;

int main(int argc, const char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <party>" << std::endl;
        return 1;
    }
    int party = argv[1][0] - '0';
    assert((party == 1 || party == 2) && "Party must be 1 or 2");

    unsigned int num_feature = 128, comm_dim = 768, output_size = 64;
    SimpleNet* net = new SimpleNet(party, num_feature, comm_dim, output_size);
    std::cout << "SimpleNet created" << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint64_t> uint64_dist(0, 1);
    std::uniform_real_distribution<double> real_dist(-1.0, 1.0);
    Data input, output;
    input.HEData = vector<vector<vector<uint64_t>>>(num_feature, vector<vector<uint64_t>>(num_feature, vector<uint64_t>(comm_dim)));
    input.NexusData = vector<vector<vector<double>>>(num_feature, vector<vector<double>>(num_feature, vector<double>(comm_dim)));
    for (unsigned int i = 0; i < num_feature; i++) {
        for (unsigned int j = 0; j < num_feature; j++) {
            for (unsigned int k = 0; k < comm_dim; k++) {
                input.HEData[i][j][k] = uint64_dist(gen);
                input.NexusData[i][j][k] = real_dist(gen);
            }
        }
    }

    net->forward(input, output);

    delete net;
    return 0;
}