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
        .damage = 7,
        .armorValue = 0,
        .heal = 0,
        .minFloor = 1
    };
    inline ItemData Sword 
    {
        .name = "Sword",
        .description = "A sword, once used in a great war.",
        .price = 135,
        .type = ItemType::Weapon,
        .damage = 9,
        .armorValue = 0,
        .heal = 0,
        .minFloor = 3
    };
    inline ItemData ThrowingCard 
    {
        .name = "Throwing Card",
        .description = "A thick card that can heftly slice enemies.",
        .price = 650,
        .type = ItemType::Weapon,
        .damage = 15,
        .armorValue = 0,
        .heal = 0,
        .minFloor = 6
    };
    inline ItemData Vest 
    {
        .name = "Vest",
        .description = "A strong vest that protects against many wounds.",
        .price = 750,
        .type = ItemType::Armor,
        .damage = 0,
        .armorValue = 2,
        .heal = 0,
        .minFloor = 3
    };
    inline ItemData Chainmail 
    {
        .name = "Chainmail",
        .description = "A shirt of chainmail, with slight rust.",
        .price = 1500,
        .type = ItemType::Armor,
        .damage = 0,
        .armorValue = 4,
        .heal = 0,
        .minFloor = 5
    };
    inline ItemData GuardsHide
    {
        .name = "Guard's Hide",
        .description = "Stolen from a guard. A thick coat.",
        .price = 2500,
        .type = ItemType::Armor,
        .damage = 0,
        .armorValue = 7,
        .heal = 0,
        .minFloor = 7
    };
    inline ItemData Potion 
    {
        .name = "Potion",
        .description = "Heals a small amount.",
        .price = 130,
        .type = ItemType::Consumable,
        .damage = 0,
        .armorValue = 0,
        .heal = 20,
        .minFloor = 1
    };
    inline ItemData LargePotion 
    {
        .name = "Large Potion",
        .description = "Heals a good amount.",
        .price = 250,
        .type = ItemType::Consumable,
        .damage = 0,
        .armorValue = 0,
        .heal = 40,
        .minFloor = 4
    };
    inline ItemData Attack 
    {
        .name = "Attack",
        .description = "Allows an attack.",
        .price = 100,
        .type = ItemType::Attack,
        .damage = 0,
        .armorValue = 0,
        .heal = 0,
        .minFloor = 1
    };
}
