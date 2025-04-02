#pragma once
#include <string>
#include <vector>

#include "config.h"
using namespace nisl;

class OP {
public:
    const int party;
    const MPCType type;

    OP(const int _party, MPCType _type): party(_party), type(_type) {}
};