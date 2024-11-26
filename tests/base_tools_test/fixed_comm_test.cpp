#include "emp-ot.h"
#include "emp-tool.h"
#include "ring-op.h"

using namespace nisl;

int main(int argc, const char** argv) {
    if (argc > 1) {
        int party_ = argv[1][0] - '0';
        assert(party_ == ALICE || party_ == BOB);

        IOPack* iopack = new IOPack(party_, 12345);
        OTPack* otpack = new OTPack(iopack, party_);

        uint64_t* data;
        data  = new uint64_t;
        *data = 1;

        if (party_ == ALICE) {
            std::cout << "Party: ALICE"
                      << "\n";
        }
        else if (party_ == BOB) {
            std::cout << "Party: BOB"
                      << "\n";
        }

        FixArray* fix = new FixArray(ALICE, 10, true, 37, 12);

        if (party_ == ALICE) {
            std::cout << "start \n";
            iopack->io->send_data(data, 1);
            std::cout << "success \n";
        }
        else if (party_ == BOB) {
            // uint64_t *data;
            std::cout << "start \n";
            iopack->io->recv_data(data, 1);
            std::cout << "success \n";
        }
        uint64_t a = std::numeric_limits<uint64_t>::max();
        std::cout << a << "\n";

        delete iopack;
        delete fix;
    }
}