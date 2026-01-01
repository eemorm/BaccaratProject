#pragma once

// Custom Includes
#include "Edge.hpp"

class PlayerStats
{
    private:
        float maxHealthBonus = 0.f;
        float bankerReturnMultiplierBonus = 0.f;
        float tieReturnMultiplierBonus = 0.f;
        float playerReturnMultiplierBonus = 0.f;
        float floorMoneyReturnBonus = 0.f;
        float healingBonus = 0.f;
        float shopPercentOffBonus = 0.f;
        float attackPercentOffBonus = 0.f;
    public:
        float getMaxHealthBonus() { return maxHealthBonus; }
        float getBankerReturnMultiplierBonus() { return bankerReturnMultiplierBonus; }
        float getTieReturnMultiplierBonus() { return tieReturnMultiplierBonus; }
        float getPlayerReturnMultiplierBonus() { return playerReturnMultiplierBonus; }
        float getFloorMoneyReturnBonus() { return floorMoneyReturnBonus; }
        float getHealingBonus() { return healingBonus; }
        float getShopPercentOffBonus() { return shopPercentOffBonus; }
        float getAttackPercentOffBonus() { return attackPercentOffBonus; }

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
                case EdgeType::Interest:
                    floorMoneyReturnBonus += edge.value;
                    break;
                case EdgeType::Healing:
                    healingBonus += edge.value;
                    break;
                case EdgeType::MoneyOff:
                    if (shopPercentOffBonus < 0.5 && edge.name == "Yard Sale")
                        shopPercentOffBonus += edge.value;
                    if (attackPercentOffBonus < 0.5 && edge.name == "Bloody Key")
                        attackPercentOffBonus += edge.value;
                    break;
            }
        }
};