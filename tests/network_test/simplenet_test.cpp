// #include "simplenet.h"
// using std::vector;
// using namespace nisl;
// int dim[4][3];
// int party, port = 32000, d = 0;
// string address = "127.0.0.1";

// int main(int argc, char** argv) {
//     ArgMapping amap;
//     amap.arg("r", party, "Role of party: ALICE = 1; BOB = 2");
//     amap.arg("p", port, "Port Number");
//     amap.arg("ip", address, "IP Address of server (ALICE)");
//     amap.arg("d", d, "dim of mat");
//     amap.parse(argc, argv);

//     if (party == ALICE) {
//         std::cout << "Party: ALICE"
//                   << "\n";
//     }
//     else if (party == BOB) {
//         std::cout << "Party: BOB"
//                   << "\n";
//     }
//     SimpleNet simnet = new SimpleNet(party, 128, 768, 64);
//     std::cout << "Start inference! ";
//     simnet.forward();
// }