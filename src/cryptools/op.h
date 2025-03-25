#pragma once
#include <string>
#include <vector>

#include "config.h"
using namespace nisl;

class OP {
public:
    const int party;
    std::vector<std::string> OPs;
    const MPCType type;

    OP(const int _party, MPCType _type): party(_party), type(_type) {}
};