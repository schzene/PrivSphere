
#include "emp-tool.h"
#include "nexus-op.h"

using std::vector;
using namespace nisl;
int dim[4][3];
int party, port = 32000, d = 0;
string address = "127.0.0.1";

int main(int argc, char** argv) {
    ArgMapping amap;
    amap.arg("r", party, "Role of party: ALICE = 1; BOB = 2");
    amap.arg("p", port, "Port Number");
    amap.arg("ip", address, "IP Address of server (ALICE)");
    amap.arg("d", d, "dim of mat");
    amap.parse(argc, argv);

    if (party == ALICE) {
        std::cout << "Party: ALICE"
                  << "\n";
    }
    else if (party == BOB) {
        std::cout << "Party: BOB"
                  << "\n";
    }

    int dim1 = 768, dim2 = 64, dim3 = 128;
    nisl::IOPack* iopack = new nisl::IOPack(party, port, address);
    nisl::NetIO* io      = iopack->io;
    uint64_t base_mod    = 2198100901889;

    NEXUS_op* nexusop = new NEXUS_op(party, io);

    Data myData, dataW;

    size_t depth = 4;
    size_t rows  = 4;
    size_t cols  = 4;

    myData.NexusData = vector<vector<vector<double>>>(depth, vector<vector<double>>(rows, vector<double>(cols)));

    dataW.NexusData = vector<vector<vector<double>>>(depth, vector<vector<double>>(rows, vector<double>(cols)));

    for (size_t i = 0; i < depth; ++i) {
        for (size_t j = 0; j < rows; ++j) {
            for (size_t k = 0; k < cols; ++k) {
                myData.NexusData[i][j][k] = static_cast<double>(i * rows * cols + j * cols + k);
                dataW.NexusData[i][j][k] = static_cast<double>(i * rows * cols + j * cols + k);
            }
        }
    }
    for (size_t i = 0; i < depth; ++i) {
        std::cout << "Depth " << i << ":" << endl;
        for (size_t j = 0; j < rows; ++j) {
            for (size_t k = 0; k < cols; ++k) {
                std::cout << myData.NexusData[i][j][k] << " ";
            }
            std::cout << endl;
        }
        std::cout << endl;
    }

    auto start = iopack->get_comm();
    Data out;
    INIT_TIMER
    START_TIMER
    nexusop->fc(myData, dataW, out);
    // nexusop->softmax(myData, out);
    // nexusop->ln(myData, out);
    // nexusop->gelu(myData, out);
    // for (int i = 0; i < dim1; i++) {
    //     // cheetahln->fc(input[i], weight, meta, out[i]);
        
    //     // std::cout << "error";
    // }
    STOP_TIMER("fc")
    std::cout << "comm: " << (iopack->get_comm() - start) / 1024 << "\n";
}