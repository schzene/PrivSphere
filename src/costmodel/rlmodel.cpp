#include "rlmodel.h"

#include <algorithm>
#include <iostream>

std::string SimpleRLModel::chooseTechnique(const std::string& op_name, double he_cost, double ss_cost,
                                           double transition_cost, double he_bootstrap_cost) {
    // Calculate the total costs
    double total_he_cost = he_cost + he_bootstrap_cost;
    double total_ss_cost = ss_cost + transition_cost;

    // Choose the technique with the minimal cost
    if (total_he_cost < total_ss_cost) {
        return "HE";
    }
    else {
        return "SS";
    }
}

std::vector<std::string> SimpleRLModel::optimizeSequence(const std::vector<std::string>& op_sequence,
                                                         const std::map<std::string, double>& he_costs,
                                                         const std::map<std::string, double>& ss_costs,
                                                         double transition_cost_he_to_ss,
                                                         double transition_cost_ss_to_he, double he_bootstrap_cost) {
    std::vector<std::string> techniques;
    std::string prev_technique = "";
    int he_consecutive_count   = 0;

    for (const auto& op_name : op_sequence) {
        double he_cost = he_costs.at(op_name);
        double ss_cost = ss_costs.at(op_name);

        double transition_cost = 0.0;
        if (prev_technique == "HE") {
            transition_cost = transition_cost_he_to_ss;
        }
        else if (prev_technique == "SS") {
            transition_cost = transition_cost_ss_to_he;
        }

        double bootstrap_cost = (he_consecutive_count >= 5) ? he_bootstrap_cost : 0.0;

        std::string technique = chooseTechnique(op_name, he_cost, ss_cost, transition_cost, bootstrap_cost);
        techniques.push_back(technique);

        // Update state
        if (technique == "HE") {
            he_consecutive_count++;
        }
        else {
            he_consecutive_count = 0;
        }
        prev_technique = technique;
    }

    return techniques;
}