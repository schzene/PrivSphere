#include "protocols.h"

void load_data(vector<vector<vector<uint64_t>>> &A, size_t dim1, size_t dim2, size_t dim3) {
    A = vector<vector<vector<uint64_t>>>(dim1, vector<vector<uint64_t>>(dim2, vector<uint64_t>(dim3, 1)));
}

void load_data(vector<vector<uint64_t>> B, size_t dim1, size_t dim2) {
    B = vector<vector<uint64_t>>(dim1, vector<uint64_t>(dim2, 1));
}