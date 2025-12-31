#pragma once

// SFML
#include <SFML/Graphics.hpp>

class PlayerHealth
{
    private:
        int maxHealth;
        int currentHealth;
    public:
        PlayerHealth(int h) : maxHealth(h), currentHealth(h) {}
        int getMaxHealth() { return maxHealth; }
        int getCurrentHealth() { return currentHealth; }
        void heal(int amount) { currentHealth = std::min(maxHealth, currentHealth + amount); }
        void takeDamage(int damage, int armorValue) { int finalDamage = std::max(0, damage - armorValue / 2); currentHealth -= finalDamage; }
        bool isDead() const { return currentHealth <= 0; }
};