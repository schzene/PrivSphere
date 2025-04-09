#include "abstractop.h"

#include <iostream>

// Constructor
MLIRParser::MLIRParser(std::shared_ptr<CostModel> he_cost_model, std::shared_ptr<CostModel> ss_cost_model,
                       std::shared_ptr<RLModel> rl_model)
    : he_cost_model(he_cost_model),
      ss_cost_model(ss_cost_model),
      rl_model(rl_model),
      prev_technique(""),
      he_consecutive_count(0) {}

// Execute a sequence of MLIR operations
void MLIRParser::executeSequence(const std::vector<std::string>& op_sequence) {
    for (const auto& op_name : op_sequence) {
        std::string technique = decideTechnique(op_name, prev_technique);

        // Update consecutive HE count
        if (technique == "HE") {
            he_consecutive_count++;
        }
        else {
            he_consecutive_count = 0;  // Reset if not HE
        }

        // Execute the operation
        executeOperation(op_name, technique);

        // Update previous technique
        prev_technique = technique;
    }
}

// Decide between HE or SS for a given operation
std::string MLIRParser::decideTechnique(const std::string& op_name, const std::string& prev_technique) {
    double he_cost = he_cost_model->estimateCost(op_name, "HE");
    double ss_cost = ss_cost_model->estimateCost(op_name, "SS");

    // Add transition cost if switching between HE and SS
    if (!prev_technique.empty() && prev_technique != "HE") {
        he_cost += he_cost_model->getTransitionCost("SS_to_HE");
    }
    if (!prev_technique.empty() && prev_technique != "SS") {
        ss_cost += ss_cost_model->getTransitionCost("HE_to_SS");
    }

    // Add bootstrapping cost if too many consecutive HE
    if (he_consecutive_count >= 5) {
        he_cost += he_cost_model->getBootstrappingCost();
    }

    // Use RL model to decide the best technique
    return rl_model->chooseTechnique(op_name, he_cost, ss_cost);
}

// Execute a single operation
void MLIRParser::executeOperation(const std::string& op_name, const std::string& technique) {
    std::cout << "Executing operation: " << op_name << " using technique: " << technique << std::endl;
    if (technique == "HE") {
        std::cout << "Simulating HE execution for " << op_name << std::endl;
    }
    else if (technique == "SS") {
        std::cout << "Simulating SS execution for " << op_name << std::endl;
    }
}

// Implementations of TOSA operations
void MLIRParser::tosa_const(int index) {
    std::cout << "Executing tosa_const at index " << index << std::endl;
}

void MLIRParser::tosa_transpose(int index) {
    std::cout << "Executing tosa_transpose at index " << index << std::endl;
}

void MLIRParser::tosa_reshape(int index, const std::vector<int64_t>& new_shape) {
    std::cout << "Executing tosa_reshape at index " << index << " with new shape: ";
    for (const auto& dim : new_shape) {
        std::cout << dim << " ";
    }
    std::cout << std::endl;
}

void MLIRParser::tosa_matmul(int index) {
    std::cout << "Executing tosa_matmul at index " << index << std::endl;
}

void MLIRParser::tosa_add(int index) {
    std::cout << "Executing tosa_add at index " << index << std::endl;
}

void MLIRParser::tosa_gather(int index) {
    std::cout << "Executing tosa_gather at index " << index << std::endl;
}

void MLIRParser::tosa_reduce_max(int index) {
    std::cout << "Executing tosa_reduce_max at index " << index << std::endl;
}

void MLIRParser::tosa_sub(int index) {
    std::cout << "Executing tosa_sub at index " << index << std::endl;
}

void MLIRParser::tosa_exp(int index) {
    std::cout << "Executing tosa_exp at index " << index << std::endl;
}

void MLIRParser::tosa_reduce_sum(int index) {
    std::cout << "Executing tosa_reduce_sum at index " << index << std::endl;
}

void MLIRParser::tosa_reciprocal(int index) {
    std::cout << "Executing tosa_reciprocal at index " << index << std::endl;
}

void MLIRParser::tosa_mul(int index) {
    std::cout << "Executing tosa_mul at index " << index << std::endl;
}

void MLIRParser::tosa_rsqr(int index) {
    std::cout << "Executing tosa_rsqr at index " << index << std::endl;
}

void MLIRParser::tosa_tile(int index, const std::vector<int64_t>& multiples) {
    std::cout << "Executing tosa_tile at index " << index << " with multiples: ";
    for (const auto& multiple : multiples) {
        std::cout << multiple << " ";
    }
    std::cout << std::endl;
}

void MLIRParser::tosa_abs(int index) {
    std::cout << "Executing tosa_abs at index " << index << std::endl;
}

void MLIRParser::tosa_greater_equal(int index) {
    std::cout << "Executing tosa_greater_equal at index " << index << std::endl;
}

void MLIRParser::tosa_negate(int index) {
    std::cout << "Executing tosa_negate at index " << index << std::endl;
}

void MLIRParser::tosa_select(int index) {
    std::cout << "Executing tosa_select at index " << index << std::endl;
}