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
        "+0.5x Return on Banker",
        EdgeType::BankerChipReturn,
        0.5f
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
        "+0.5x Return on Player",
        EdgeType::PlayerChipReturn,
        0.5f
    };
    inline Edge Monopoly
    {
        "Monopoly",
        "+$100 Gained Extra Per Floor",
        EdgeType::Interest,
        100.f
    };
    inline Edge Parasite
    {
        "Parasite",
        "Extra 15 Health for Every Heal",
        EdgeType::Healing,
        15.f
    };
    inline Edge YardSale
    {
        "Yard Sale",
        "5% Off of Every Shop Item (Excluding Attacks)",
        EdgeType::MoneyOff,
        0.05f
    };
    inline Edge BloodyKey
    {
        "Bloody Key",
        "5% Off of Attacks",
        EdgeType::MoneyOff,
        0.05f
    };
}