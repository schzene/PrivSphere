#include "data_process.h"

void convert(unsigned party, const MPCType s, const MPCType t, const Data& i, Data& o) {
    o = Data();
    switch (s) {
        case MPCType::HE:
            switch (t) {
                case MPCType::HE:
                    o.HEData = i.HEData;
                    return;
                case MPCType::SS:
                    return;
                case MPCType::NEXUS:
                    o.NexusData = vector<vector<vector<double>>>(
                        i.HEData.size(),
                        vector<vector<double>>(i.HEData[0].size(), vector<double>(i.HEData[0][0].size(), 0.0)));
                    return;
            }
            return;
        case MPCType::SS:
            switch (t) {
                case MPCType::HE:
                    return;
                case MPCType::SS:
                    o.SSData = i.SSData;
                    return;
                case MPCType::NEXUS:
                    return;
            }
            return;
        case MPCType::NEXUS:
            switch (t) {
                case MPCType::HE:
                    o.HEData = vector<vector<vector<uint64_t>>>(
                        i.NexusData.size(),
                        vector<vector<uint64_t>>(i.NexusData[0].size(), vector<uint64_t>(i.NexusData[0][0].size(), 0)));
                    return;
                case MPCType::SS:
                    return;
                case MPCType::NEXUS:
                    o.NexusData = i.NexusData;
                    return;
            }
            return;
    }
}

void load_data(vector<vector<vector<uint64_t>>>& A, size_t dim1, size_t dim2, size_t dim3) {
    A = vector<vector<vector<uint64_t>>>(dim1, vector<vector<uint64_t>>(dim2, vector<uint64_t>(dim3, 1)));
}

void load_data(vector<vector<uint64_t>> B, size_t dim1, size_t dim2) {
    B = vector<vector<uint64_t>>(dim1, vector<uint64_t>(dim2, 1));
}