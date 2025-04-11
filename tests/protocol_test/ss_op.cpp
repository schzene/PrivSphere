#include "FloatingPoint/fixed-point.h"
#include "OT/ot_pack.h"
#include "config.h"
#include "utils/io_pack.h"
#include <iostream>
#include <random>

using namespace std;

map<string, int> op_map = {
    {"add",        0 },
    {"sub",        1 },
    {"mul",        2 },
    {"div",        3 },
    {"exp",        4 },
    {"sqrt",       5 },
    {"abs",        6 },
    {"GE",         7 },
    {"reciprocal", 10},
    {"if_else",    11}
};

int get_op(const string& op_name) {
    auto it = op_map.find(op_name);
    if (it != op_map.end()) {
        return it->second;
    } else {
        cerr << "Invalid operation name: " << op_name << endl;
        exit(EXIT_FAILURE);
    }
}

int main(int argc, const char** argv) {
    assert(argc >= 3 && "Usage: ./ss_add <party> <op> <size>");
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint64_t> dist(0, 1ULL << nisl::ELL);

    int party = atoi(argv[1]), op = get_op(argv[2]), size = atoi(argv[3]);
    assert(party == sci::ALICE || party == sci::BOB);

    FixArray fa(party, size, false, nisl::ELL, nisl::SCALE);
    FixArray fb(party, size, false, nisl::ELL, nisl::SCALE);

    for (int i = 0; i < size; i++) {
        fa.data[i] = dist(gen);
        fb.data[i] = dist(gen);
    }

    sci::IOPack* iopack = new sci::IOPack(party, 32000);
    sci::OTPack* otpack = new sci::OTPack(iopack, party);
    FixOp* fop = new FixOp(party, iopack, otpack);

    BoolArray cond = fop->GE(fa, fb);

    auto comm_start = iopack->get_comm();
    auto start = std::chrono::high_resolution_clock::now();
    switch (op) {
    case 0:
        fop->add(fa, fb);
        break;
    case 1:
        fop->sub(fa, fb);
        break;
    case 2:
        fop->mul(fa, fb);
        break;
    case 3:
        fop->div(fa, fb, nisl::ELL, nisl::SCALE);
        break;
    case 4:
        fop->exp(fa, nisl::ELL, nisl::SCALE);
        break;
    case 5:
        fop->sqrt(fa);
        break;
    case 6:
        fop->abs(fa);
        break;
    case 7:
        fop->GE(fa, fb);
        break;
    case 10:
        fop->reciprocal(fa, nisl::ELL, nisl::SCALE);
        break;
    case 11:
        fop->if_else(cond, fa, fb);
        break;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto comm_end = iopack->get_comm();
    auto comm = comm_end - comm_start;

    std::cout << "Size of data: " << size << std::endl;
    std::cout << "Time of " << argv[2] << ": "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us"
              << std::endl;
    std::cout << "Communication: " << comm << " B" << std::endl;
    delete fop;
    delete otpack;
    delete iopack;
    return 0;
}