#pragma once

// Custom Includes
#include "Enemy.hpp"

namespace EnemyDB
{
    inline EnemyData Rat
    {
        .name = "Rat",
        .maxHealth = 20,
        .armorValue = 0,
        .attackDamage = 3,
        .level = 1,
        .color = sf::Color::Green
    };
    inline EnemyData Thug 
    {
        .name = "Thug",
        .maxHealth = 50,
        .armorValue = 2,
        .attackDamage = 7,
        .level = 2,
        .color = sf::Color::Red
    };
    inline EnemyData Guard 
    {
        .name = "Guard",
        .maxHealth = 60,
        .armorValue = 4,
        .attackDamage = 8,
        .level = 3,
        .color = sf::Color::Blue
    };
}
