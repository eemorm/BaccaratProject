#pragma once

// Custom Includes
#include "PlayerStats.hpp"

// SFML
#include <SFML/Graphics.hpp>

class PlayerHealth
{
    private:
        int maxHealth;
        int currentHealth;
        PlayerStats& playerStats;
    public:
        PlayerHealth(int h, PlayerStats& ps) : maxHealth(h), currentHealth(h), playerStats(ps) {}
        int getMaxHealth() { return maxHealth + playerStats.getMaxHealthBonus(); }
        int getCurrentHealth() { return currentHealth; }
        void heal(int amount) { currentHealth = std::min(getMaxHealth(), currentHealth + amount); }
        void takeDamage(int damage, int armorValue) { int finalDamage = std::max(0, damage - armorValue / 2); currentHealth -= finalDamage; }
        bool isDead() const { return currentHealth <= 0; }
};