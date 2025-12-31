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
    public:
        PlayerCombat(Inventory* i) : playerInventory(i) {}
        Inventory& getPlayerInventory() { return *playerInventory; }
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
};