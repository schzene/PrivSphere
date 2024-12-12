#ifndef CHEETAH_OP_H__
#define CHEETAH_OP_H__
#include <vector>

#include "cheetah-api.h"
#include "config.h"
#include "emp-tool.h"
#include "tensor_shape.h"

using std::vector;
using namespace nisl;
using namespace gemini;
/**
 * A simple CHEETAH interface, with secondary encapsulation, makes it support PrivSphere's contex
 */
// "127.0.0.1"
//  = 12345
class Cheetah_op {
public:
    int party;
    static const Type type = Type::HE;
    typedef vector<vector<vector<uint64_t>>> Type;

    CheetahLinear* linear;

    Cheetah_op(int party, NetIO* io, uint64_t base_mod = 1ULL << ELL, size_t nthreads = 1) {
        this->party  = party;
        this->linear = new CheetahLinear(party, io, base_mod, nthreads);
    }

    ~Cheetah_op() {
        delete linear;
    }

    void conv2d(const vector<vector<vector<uint64_t>>>& input, const vector<vector<vector<vector<uint64_t>>>>& kernel,
                size_t stride, vector<vector<vector<uint64_t>>>& output);

    void fc(const vector<vector<vector<uint64_t>>>& input, const vector<vector<vector<uint64_t>>>& weight,
            vector<vector<vector<uint64_t>>>& output);

    void bn(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output,
            const uint64_t scale);

    void bn_direct();

    static vector<vector<vector<uint64_t>>> from_tensor(const Tensor<uint64_t>& tensor);
    static Tensor<uint64_t> to_tensor(const vector<vector<vector<uint64_t>>>& input);
    static Tensor<uint64_t> to_tensor(const uint64_t input, unsigned int shape1, unsigned int shape2,
                                      unsigned int shape3);

private:
    /* data */
};

#endif  // CHEETAH_OP_H__
