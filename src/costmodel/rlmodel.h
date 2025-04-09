#ifndef RLMODEL_H
#define RLMODEL_H

#include <map>
#include <string>
#include <vector>

class RLModel {
public:
    virtual ~RLModel() = default;

    // Select the best technique (HE or SS) for a given operation
    virtual std::string chooseTechnique(const std::string& op_name, double he_cost, double ss_cost,
                                        double transition_cost, double he_bootstrap_cost) = 0;

    // Optimize the entire sequence of operations
    virtual std::vector<std::string> optimizeSequence(const std::vector<std::string>& op_sequence,
                                                      const std::map<std::string, double>& he_costs,
                                                      const std::map<std::string, double>& ss_costs,
                                                      double transition_cost_he_to_ss, double transition_cost_ss_to_he,
                                                      double he_bootstrap_cost) = 0;
};

class SimpleRLModel : public RLModel {
public:
    std::string chooseTechnique(const std::string& op_name, double he_cost, double ss_cost, double transition_cost,
                                double he_bootstrap_cost) override;

    std::vector<std::string> optimizeSequence(const std::vector<std::string>& op_sequence,
                                              const std::map<std::string, double>& he_costs,
                                              const std::map<std::string, double>& ss_costs,
                                              double transition_cost_he_to_ss, double transition_cost_ss_to_he,
                                              double he_bootstrap_cost) override;
};

#endif  // RLMODEL_H