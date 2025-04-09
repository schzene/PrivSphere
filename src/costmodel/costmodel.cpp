#include "costmodel.h"

// HE Cost Model
double HECostModel::estimateCost(const std::string& op_name, const std::string& technique) {
    if (op_name == "tosa_matmul") {
        return 120.0;  // Example cost for HE matmul
    }
    return 100.0;  // Default HE cost
}

double HECostModel::getTransitionCost(const std::string& transition) {
    if (transition == "SS_to_HE") {
        return 50.0;  // Example transition cost
    }
    return 0.0;
}

double HECostModel::getBootstrappingCost() {
    return 200.0;  // Example bootstrapping cost
}

// SS Cost Model
double SSCostModel::estimateCost(const std::string& op_name, const std::string& technique) {
    if (op_name == "tosa_matmul") {
        return 60.0;  // Example cost for SS matmul
    }
    return 50.0;  // Default SS cost
}

double SSCostModel::getTransitionCost(const std::string& transition) {
    if (transition == "HE_to_SS") {
        return 30.0;  // Example transition cost
    }
    return 0.0;
}

double SSCostModel::getBootstrappingCost() {
    return 0.0;  // SS does not require bootstrapping
}