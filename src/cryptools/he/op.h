#pragma once
#include <string>
#include <vector>

#include "config.h"

class OP {
public:
    const int party;
    std::vector<std::string> OPs;
    static const MPCType type;

    OP(const int _party): party(_party) {}
};