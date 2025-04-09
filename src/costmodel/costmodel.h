#ifndef COSTMODEL_H
#define COSTMODEL_H

#include <string>

class CostModel {
public:
    virtual ~CostModel() = default;

    // Estimate the cost of using a specific technique (HE or SS)
    virtual double estimateCost(const std::string& op_name, const std::string& technique) = 0;

    // Get the cost of transitioning between HE and SS
    virtual double getTransitionCost(const std::string& transition) = 0;

    // Get the cost of HE bootstrapping
    virtual double getBootstrappingCost() = 0;
};

class HECostModel : public CostModel {
public:
    double estimateCost(const std::string& op_name, const std::string& technique) override;
    double getTransitionCost(const std::string& transition) override;
    double getBootstrappingCost() override;
};

class SSCostModel : public CostModel {
public:
    double estimateCost(const std::string& op_name, const std::string& technique) override;
    double getTransitionCost(const std::string& transition) override;
    double getBootstrappingCost() override;
};

#endif  // COSTMODEL_H