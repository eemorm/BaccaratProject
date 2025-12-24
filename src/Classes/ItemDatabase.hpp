#pragma once

// Custom Includes
#include "Item.hpp"

namespace ItemDB 
{
    inline ItemData Dagger 
    {
        .name = "Dagger",
        .description = "A dagger. Used for slashing foes.",
        .price = 50,
        .type = ItemType::Weapon,
        .damage = 5,
        .armorValue = 0
    };
    inline ItemData Vest 
    {
        .name = "Kevlar Vest",
        .description = "A strong vest that protects against many wounds.",
        .price = 75,
        .type = ItemType::Armor,
        .damage = 0,
        .armorValue = 3
    };
    inline ItemData Heal 
    {
        .name = "Heal",
        .description = "Heals a good amount.",
        .price = 20,
        .type = ItemType::Consumable,
        .damage = 0,
        .armorValue = 0
    };
}
