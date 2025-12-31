#pragma once

// Custom Includes
#include "Item.hpp"
#include "PlayerHealth.hpp"

// SFML
#include <SFML/Graphics.hpp>

// Standard Libraries
#include <string>
#include <memory>

class Inventory 
{
    private:
        std::unique_ptr<Item> equippedWeapon;
        std::unique_ptr<Item> equippedArmor;

        PlayerHealth* playerHealth;

        int attacks = 0;
    public:
        Inventory(PlayerHealth* h) : playerHealth(h) {}
        PlayerHealth* getPlayerHealth() { return playerHealth; }
        Item* getEquippedWeapon() { return equippedWeapon.get(); }
        Item* getEquippedArmor() { return equippedArmor.get(); }
        void equipWeapon(std::unique_ptr<Item> weapon) { equippedWeapon = std::move(weapon); }
        void equipArmor(std::unique_ptr<Item> armor) { equippedArmor = std::move(armor); }
        int getAttacks() { return attacks; }
        void addAttack(int amount) { attacks += amount; }
        void useAttack()
        {
            if (attacks <= 0)
                return;
            attacks--;
        }
};