#pragma once

// Custom Includes
#include "Enemy.hpp"

namespace EnemyDB
{
    inline EnemyData Insect
    {
        .name = "Insect",
        .maxHealth = 20,
        .armorValue = 0,
        .attackDamage = 3,
        .level = 1,
        .color = sf::Color::Green,
        .minFloor = 1
    };
    inline EnemyData Rat
    {
        .name = "Rat",
        .maxHealth = 25,
        .armorValue = 0,
        .attackDamage = 4,
        .level = 1,
        .color = sf::Color::Black,
        .minFloor = 2
    };
    inline EnemyData Reaper 
    {
        .name = "Reaper",
        .maxHealth = 35,
        .armorValue = 1,
        .attackDamage = 7,
        .level = 2,
        .color = sf::Color::Yellow,
        .minFloor = 4
    };
    inline EnemyData Thug 
    {
        .name = "Thug",
        .maxHealth = 50,
        .armorValue = 2,
        .attackDamage = 7,
        .level = 2,
        .color = sf::Color::Red,
        .minFloor = 5
    };
    inline EnemyData Guard 
    {
        .name = "Guard",
        .maxHealth = 60,
        .armorValue = 4,
        .attackDamage = 8,
        .level = 3,
        .color = sf::Color::Blue,
        .minFloor = 6
    };
    inline EnemyData Executioner 
    {
        .name = "Executioner",
        .maxHealth = 85,
        .armorValue = 2,
        .attackDamage = 9,
        .level = 3,
        .color = sf::Color::Blue,
        .minFloor = 8
    };
}
