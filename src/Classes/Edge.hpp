#pragma once

// Standard Libraries
#include <string>

enum class EdgeType
{
    MaxHealth,
    BankerChipReturn,
    TieChipReturn,
    PlayerChipReturn,
    Interest
};

struct Edge
{
    std::string name;
    std::string description;
    EdgeType type;
    float value;
};
