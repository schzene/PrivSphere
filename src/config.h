#pragma once

#include <cstdint>
#include <vector>
using std::vector;

namespace nisl {
const static int AES_BATCH_SIZE = 2048;
// const static int AES_BATCH_SIZE = 256;
const static int HASH_BUFFER_SIZE = 1024 * 8;
const static int NETWORK_BUFFER_SIZE =
    1024 * 16; // Should change depending on the network
const static int FILE_BUFFER_SIZE = 1024 * 16;
const static int CHECK_BUFFER_SIZE = 1024 * 8;

const static int XOR = -1;
const static uint8_t ELL = 31;
const static uint8_t SCALE = 13;

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
}