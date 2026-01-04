#pragma once

// Custom Includes
#include "../textures.hpp"
#include "Enemy.hpp"

namespace EnemyDB
{
    inline EnemyData Insect
    {
        .texture = &insectTexture,
        .name = "Insect",
        .maxHealth = 20,
        .armorValue = 0,
        .attackDamage = 3,
        .level = 1,
        .minFloor = 1
    };
    inline EnemyData Rat
    {
        .texture = &ratTexture,
        .name = "Rat",
        .maxHealth = 25,
        .armorValue = 0,
        .attackDamage = 4,
        .level = 1,
        .minFloor = 2
    };
    inline EnemyData Reaper 
    {
        .texture = &reaperTexture,
        .name = "Reaper",
        .maxHealth = 35,
        .armorValue = 1,
        .attackDamage = 7,
        .level = 2,
        .minFloor = 4
    };
    inline EnemyData Thug 
    {
        .texture = &thugTexture,
        .name = "Thug",
        .maxHealth = 50,
        .armorValue = 2,
        .attackDamage = 7,
        .level = 2,
        .minFloor = 5
    };
    inline EnemyData Guard 
    {
        .texture = &guardTexture,
        .name = "Guard",
        .maxHealth = 60,
        .armorValue = 4,
        .attackDamage = 8,
        .level = 3,
        .minFloor = 6
    };
    inline EnemyData Executioner 
    {
        .texture = &executionerTexture,
        .name = "Executioner",
        .maxHealth = 85,
        .armorValue = 2,
        .attackDamage = 9,
        .level = 3,
        .minFloor = 8
    };
}
