#pragma once

// Standard Libraries
#include <string>

enum class EdgeType
{
    MaxHealth,
    Healing,
    BankerChipReturn,
    TieChipReturn,
    PlayerChipReturn,
    Interest,
    MoneyOff
};

struct Edge
{
    std::string name;
    std::string description;
    EdgeType type;
    float value;
};
