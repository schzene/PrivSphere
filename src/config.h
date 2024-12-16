#pragma once

#include <cstdint>
#include <vector>
using std::vector;

#define ELL 31
#define SCALE 13
enum class MPCType { HE, SS, NEXUS };

struct Data {
    vector<vector<vector<uint64_t>>> HEData;
    vector<vector<vector<uint64_t>>> SSData;
    vector<vector<vector<double>>> NexusData;

    Data() {
        HEData = vector<vector<vector<uint64_t>>>();
        SSData = vector<vector<vector<uint64_t>>>();
        NexusData = vector<vector<vector<double>>>();
    }
};