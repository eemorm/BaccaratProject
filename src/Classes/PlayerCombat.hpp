#pragma once

// Custom Includes
#include "Enemy.hpp"
#include "Inventory.hpp"

// SFML
#include <SFML/Graphics.hpp>

class PlayerCombat
{
    private:
        Inventory* playerInventory;

        int maxHealth;
        int currentHealth;
    public:
        PlayerCombat(Inventory* i, int h) : playerInventory(i), maxHealth(h), currentHealth(h) {}
        Inventory& getPlayerInventory() { return *playerInventory; }
        int getMaxHealth() { return maxHealth; }
        int getCurrentHealth() { return currentHealth; }
        int getAttackDamage()
        {
            if (!playerInventory->getEquippedWeapon())
                return 0;
            return playerInventory->getEquippedWeapon()->getData()->damage;
        }
        int getArmorValue()
        {
            if (!playerInventory->getEquippedArmor())
                return 0;
            return playerInventory->getEquippedArmor()->getData()->armorValue;
        }
        void takeDamage(int damage) { int finalDamage = std::max(0, damage - getArmorValue() / 2); currentHealth -= finalDamage; }
        bool isDead() const { return currentHealth <= 0; }
};