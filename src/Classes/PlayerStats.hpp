#pragma once

// Custom Includes
#include "Edge.hpp"

class PlayerStats
{
    public:
        float maxHealthBonus = 0.f;
        float bankerReturnMultiplierBonus = 0.f;
        float tieReturnMultiplierBonus = 0.f;
        float playerReturnMultiplierBonus = 0.f;

        float getMaxHealthBonus() { return maxHealthBonus; }
        float getBankerReturnMultiplierBonus() { return bankerReturnMultiplierBonus; }
        float getTieReturnMultiplierBonus() { return tieReturnMultiplierBonus; }
        float getPlayerReturnMultiplierBonus() { return playerReturnMultiplierBonus; }

        void applyEdge(Edge& edge)
        {
            switch (edge.type)
            {
                case EdgeType::MaxHealth:
                    maxHealthBonus += edge.value;
                    break;
                case EdgeType::BankerChipReturn:
                    bankerReturnMultiplierBonus += edge.value;
                    break;
                case EdgeType::TieChipReturn:
                    tieReturnMultiplierBonus += edge.value;
                    break;
                case EdgeType::PlayerChipReturn:
                    playerReturnMultiplierBonus += edge.value;
                    break;


            }
        }
};