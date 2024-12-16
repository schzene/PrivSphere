#ifndef CHEETAH_OP_H__
#define CHEETAH_OP_H__
#include <vector>

#include "cheetah-api.h"
#include "config.h"
#include "emp-tool.h"
#include "op.h"
#include "tensor_shape.h"

using std::vector;
using namespace nisl;
using namespace gemini;
/**
 * A simple CHEETAH interface, with secondary encapsulation, makes it support PrivSphere's contex
 */
// "127.0.0.1"
//  = 12345
class Cheetah_op : public OP {
public:
    std::vector<std::string> OPs = {"conv2d", "fc", "bn"};
    static const MPCType type    = MPCType::HE;

    typedef vector<vector<vector<uint64_t>>> OPType;

    CheetahLinear* linear;

    Cheetah_op(const int party, NetIO* io, uint64_t base_mod = 1ULL << ELL, size_t nthreads = 1) : OP(party) {
        this->linear = new CheetahLinear(party, io, base_mod, nthreads);
    }

    ~Cheetah_op() {
        delete linear;
    }

    void conv2d(const Data& input, const vector<vector<vector<vector<uint64_t>>>>& kernel, size_t stride, Data& output);

    void fc(const Data& input, const Data& weight, Data& output);

    void bn(const Data& input, Data& output, const uint64_t scale);

    void bn_direct();

    static Data from_tensor(const Tensor<uint64_t>& tensor);
    static Tensor<uint64_t> to_tensor(const Data& input);
    static Tensor<uint64_t> to_tensor(const vector<vector<vector<uint64_t>>>& input);
    static Tensor<uint64_t> to_tensor(const uint64_t input, unsigned int shape1, unsigned int shape2,
                                      unsigned int shape3);
};

#endif  // CHEETAH_OP_H__
