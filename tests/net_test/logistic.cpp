#include "neuralnet/logistic.h"

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
    
    int size = 768, batch = 768;
    Logistic* log = new Logistic(party, size);
    std::cout << "Logistic created" << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint64_t> uint64_dist(0, 1);
    std::uniform_real_distribution<double> real_dist(-1.0, 1.0);

    vector<vector<uint64_t>> fix_input(size, vector<uint64_t>(batch, 0));
    vector<vector<uint64_t>> fix_output(1, vector<uint64_t>(batch, 0));

    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < batch; j++) {
            fix_input[i][j] = neg_mod(int64_t(real_dist(gen) * (1ULL << SCALE)), (1ULL << ELL));
        }
    }

    auto start = std::chrono::high_resolution_clock::now();
    log->forward(fix_input, fix_output);
    auto end = std::chrono::high_resolution_clock::now();

    printf("Time of logistic forward: %.2f s\n", 
                std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0);
    printf("Comm of logistic forward: %.2f MB\n", log->iopack->get_comm() / 1024.0 / 1024.0);

    delete log;
}