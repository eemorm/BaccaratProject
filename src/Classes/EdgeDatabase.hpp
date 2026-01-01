#pragma once

// Custom Includes
#include "Edge.hpp"

namespace EdgeDB
{
    inline Edge FleshShield
    {
        "Flesh Shield",
        "+20 Max Health",
        EdgeType::MaxHealth,
        20.f
    };
    inline Edge BankersBuff
    {
        "Banker's Buff",
        "+0.3x Return on Banker",
        EdgeType::BankerChipReturn,
        0.3f
    };
    inline Edge TiedKnot
    {
        "Tied Knot",
        "+2x Return on Tie",
        EdgeType::TieChipReturn,
        2.f
    };
    inline Edge PlayersBuff
    {
        "Players's Buff",
        "+0.3x Return on Player",
        EdgeType::PlayerChipReturn,
        0.3f
    };
    inline Edge Monopoly
    {
        "Monopoly",
        "+$100 Gained Extra Per Floor",
        EdgeType::Interest,
        100.f
    };
}