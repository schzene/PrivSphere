#ifndef CHEETAH_OP_H__
#define CHEETAH_OP_H__
#include <vector>

#include "cheetah-api.h"
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
    CheetahLinear* linear;

    Cheetah_op(int party, NetIO* io, uint64_t base_mod, size_t nthreads = 1) {
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

    void bn(const vector<vector<vector<uint64_t>>>& input, const vector<vector<vector<uint64_t>>>& scale,
            vector<vector<vector<uint64_t>>>& output);

    void bn_direct();
    
    static vector<vector<vector<uint64_t>>> from_tensor(const Tensor<uint64_t>& tensor);
    static Tensor<uint64_t> to_tensor(const vector<vector<vector<uint64_t>>>& input);

private:
    /* data */
};

#endif  // CHEETAH_OP_H__
