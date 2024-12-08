#include "cheetah-op.h"

vector<vector<vector<uint64_t>>> Cheetah_op::from_tensor(const Tensor<uint64_t>& tensor) {
    unsigned int shape1, shape2, shape3;
    if (tensor.shape().dims() == 3) {
        shape1 = tensor.shape().dim_size(0);
        shape2 = tensor.shape().dim_size(1);
        shape3 = tensor.shape().dim_size(2);
    }
    else {
        shape1 = 1;
        shape2 = tensor.shape().dim_size(0);
        shape3 = tensor.shape().dim_size(1);
    }
    vector<vector<vector<uint64_t>>> output(shape1, vector<vector<uint64_t>>(shape2, vector<uint64_t>(shape3)));
    if (tensor.shape().dims() == 3) {
        for (unsigned int i = 0; i < shape1; i++) {
            for (unsigned int j = 0; j < shape2; j++) {
                for (unsigned int k = 0; k < shape3; k++) {
                    output[i][j][k] = tensor(i, j, k);
                }
            }
        }
    }
    else {
        for (unsigned int j = 0; j < shape2; j++) {
            for (unsigned int k = 0; k < shape3; k++) {
                output[0][j][k] = tensor(j, k);
            }
        }
    }

    return output;
}

Tensor<uint64_t> Cheetah_op::to_tensor(const vector<vector<vector<uint64_t>>>& input) {
    const unsigned int shape1 = input.size(), shape2 = input[0].size(), shape3 = input[0][0].size();
    Tensor<uint64_t> input_tensor(TensorShape({shape1, shape2, shape3}));
    for (unsigned int i = 0; i < shape1; i++) {
        for (unsigned int j = 0; j < shape2; j++) {
            for (unsigned int k = 0; k < shape3; k++) {
                input_tensor(i, j, k) = input[i][j][k];
            }
        }
    }
    return input_tensor;
}

void Cheetah_op::conv2d(const vector<vector<vector<uint64_t>>>& input,
                        const vector<vector<vector<vector<uint64_t>>>>& kernel, size_t stride,
                        vector<vector<vector<uint64_t>>>& output) {
    Tensor<uint64_t> input_tensor = to_tensor(input);
    vector<Tensor<uint64_t>> kernel_tensors(kernel.size());
    for (unsigned int i = 0; i < kernel.size(); i++) {
        kernel_tensors[i] = to_tensor(kernel[i]);
    }
    CheetahLinear::ConvMeta conv_meta;
    conv_meta.ishape          = input_tensor.shape();
    conv_meta.fshape          = kernel_tensors[0].shape();
    conv_meta.n_filters       = kernel.size();
    conv_meta.padding         = Padding::SAME;
    conv_meta.stride          = stride;
    conv_meta.is_shared_input = true;

    Tensor<uint64_t> out_tensor;
    linear->conv2d(input_tensor, kernel_tensors, conv_meta, out_tensor);

    output = from_tensor(out_tensor);
}

void Cheetah_op::fc(const vector<vector<vector<uint64_t>>>& input, const vector<vector<vector<uint64_t>>>& weight,
                    vector<vector<vector<uint64_t>>>& output) {
    Tensor<uint64_t> input_tensor  = to_tensor(input);
    Tensor<uint64_t> weight_tensor = to_tensor(weight);
    CheetahLinear::FCMeta fc_meta;
    fc_meta.input_shape     = input_tensor.shape();
    fc_meta.weight_shape    = weight_tensor.shape();
    fc_meta.is_shared_input = true;

    Tensor<uint64_t> output_tensor;
    linear->fc(input_tensor, weight_tensor, fc_meta, output_tensor);

    output = from_tensor(output_tensor);
}

void Cheetah_op::bn(const vector<vector<vector<uint64_t>>>& input, const vector<vector<vector<uint64_t>>>& scale,
                    vector<vector<vector<uint64_t>>>& output) {
    Tensor<uint64_t> input_tensor = to_tensor(input);
    Tensor<uint64_t> scale_tensor = to_tensor(scale);
    CheetahLinear::BNMeta bn_meta;
    bn_meta.ishape          = input_tensor.shape();
    bn_meta.vec_shape       = scale_tensor.shape();
    bn_meta.target_base_mod = linear->base_mod();
    bn_meta.is_shared_input = true;

    Tensor<uint64_t> output_tensor;
    linear->bn(input_tensor, scale_tensor, bn_meta, output_tensor);

    output = from_tensor(output_tensor);
}
