#include <iostream>

#include "cheetah-op.h"
#include "emp-tool.h"

using namespace gemini;
using std::vector;

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

    int dim1 = 768, dim2 = 64, dim3 = 128;
    nisl::IOPack* iopack     = new nisl::IOPack(party, port, address);
    nisl::NetIO* io          = iopack->io;
    uint64_t base_mod        = 2198100901889;
    CheetahLinear* cheetahln = new CheetahLinear(party, io, base_mod, 12);

    // Cheetah_op* cheetahop = new Cheetah_op(party, address, port, base_mod, 12)

    HomFCSS::Meta meta;
    meta.input_shape     = TensorShape({dim2});
    meta.weight_shape    = TensorShape({dim3, dim2});
    meta.is_shared_input = false;

    nisl::PRG128 prg;
    vector<vector<uint64_t>> inp(dim1, vector<uint64_t>(dim2));
    vector<Tensor<uint64_t>> input(dim1), out(dim1);
    for (int i = 0; i < dim1; i++) {
        prg.random_data(inp[i].data(), dim2 * sizeof(uint64_t));
        input[i] = Tensor<uint64_t>::Wrap(inp[i].data(), meta.input_shape);
    }
    vector<uint64_t> w(dim2 * dim3);
    prg.random_data(w.data(), dim2 * dim3 * sizeof(uint64_t));
    Tensor<uint64_t> weight = Tensor<uint64_t>::Wrap(w.data(), meta.weight_shape);

    auto start = iopack->get_comm();
    INIT_TIMER
    START_TIMER
    for (int i = 0; i < dim1; i++) {
        cheetahln->fc(input[i], weight, meta, out[i]);
    }
    STOP_TIMER("fc")
    std::cout << "comm: " << iopack->get_comm() - start << "\n";
}