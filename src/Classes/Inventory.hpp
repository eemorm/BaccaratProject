#pragma once

// Custom Includes
#include "Item.hpp"

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
        std::vector<std::unique_ptr<Consumable>> consumables;

        size_t consumablesLimit = 5;
    public:
        Inventory() {}
        Weapon* getEquippedWeapon() { return equippedWeapon.get(); }
        Armor* getEquippedArmor() { return equippedArmor.get(); }
        Consumable* getConsumable(int index) { if(index < 0 || index >= consumables.size()) return nullptr; return consumables[index].get(); }
        std::vector<std::unique_ptr<Consumable>>& getConsumables() { return consumables; }
        size_t getConsumablesLimit() { return consumablesLimit; }
        void equipWeapon(std::unique_ptr<Item> weapon) { equippedWeapon = std::move(weapon); }
        void equipArmor(std::unique_ptr<Item> armor) { equippedArmor = std::move(armor); }
        void addConsumable(std::unique_ptr<Consumable> consumable) { consumables.push_back(std::move(consumable)); }
        void useConsumable(int index) 
        {
            if(index < 0 || index >= consumables.size()) return;
            consumables[index]->use();
            consumables.erase(consumables.begin() + index);
        }
};