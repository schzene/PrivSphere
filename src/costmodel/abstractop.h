#ifndef ABSTRACTOP_H
#define ABSTRACTOP_H

#include <memory>
#include <string>
#include <vector>

#include "../rl/rlmodel.h"
#include "costmodel.h"

class MLIRParser {
public:
    // Constructor
    MLIRParser(std::shared_ptr<CostModel> he_cost_model, std::shared_ptr<CostModel> ss_cost_model,
               std::shared_ptr<RLModel> rl_model);

    // Execute a sequence of MLIR operations
    void executeSequence(const std::vector<std::string>& op_sequence);

    // TOSA Operations
    void tosa_const(int index);
    void tosa_transpose(int index);
    void tosa_reshape(int index, const std::vector<int64_t>& new_shape);
    void tosa_matmul(int index);
    void tosa_add(int index);
    void tosa_gather(int index);
    void tosa_reduce_max(int index);
    void tosa_sub(int index);
    void tosa_exp(int index);
    void tosa_reduce_sum(int index);
    void tosa_reciprocal(int index);
    void tosa_mul(int index);
    void tosa_rsqr(int index);
    void tosa_tile(int index, const std::vector<int64_t>& multiples);
    void tosa_abs(int index);
    void tosa_greater_equal(int index);
    void tosa_negate(int index);
    void tosa_select(int index);

private:
    // Helper function to decide between HE or SS
    std::string decideTechnique(const std::string& op_name, const std::string& prev_technique);

    // Execute a single operation
    void executeOperation(const std::string& op_name, const std::string& technique);

    std::shared_ptr<CostModel> he_cost_model;  // Cost model for HE
    std::shared_ptr<CostModel> ss_cost_model;  // Cost model for SS
    std::shared_ptr<RLModel> rl_model;         // Reinforcement learning model

    std::string prev_technique;  // Track previous technique (HE or SS)
    int he_consecutive_count;    // Track consecutive HE operations
};

#endif  // ABSTRACTOP_H