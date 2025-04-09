#include <memory>

#include "costmodel/abstractop.h"
#include "costmodel/costmodel.h"
#include "rl/rlmodel.h"

int main() {
    // Create HE and SS cost models
    std::shared_ptr<CostModel> he_cost_model = std::make_shared<HECostModel>();
    std::shared_ptr<CostModel> ss_cost_model = std::make_shared<SSCostModel>();

    // Create RL model
    std::shared_ptr<RLModel> rl_model = std::make_shared<SimpleRLModel>();

    // Create MLIRParser instance
    MLIRParser parser(he_cost_model, ss_cost_model, rl_model);

    // Execute some operations
    parser.executeOperation("tosa_const", 0);
    parser.executeOperation("tosa_matmul", 1);
    parser.executeOperation("tosa_add", 2);

    return 0;
}