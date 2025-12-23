#pragma once

// Custom Includes
#include "Inventory.hpp"

// SFML
#include <SFML/Graphics.hpp>

// Standard Libraries
#include <string>
#include <memory>

class Shop 
{
    private:
        std::vector<ItemData*> availableItems;
        Inventory* playerInventory;
    public:
        Shop(Inventory* inv) : playerInventory(inv) {}

        void addItemToShop(ItemData* data) { availableItems.push_back(data); }
        void buyItem(int index) 
        {
            if(index < 0 || index >= availableItems.size()) return;
            if (playerInventory.getConsumables.size() < playerInventory.getConsumablesLimit()) return;

            ItemData* data = availableItems[index];

            std::unique_ptr<Item> newItem;
            switch(data->type) 
            {
                case ItemType::Weapon: 
                    playerInventory->equipWeapon(std::make_unique<Item>(data)); break;
                case ItemType::Armor: 
                    playerInventory->equipArmor(std::make_unique<Item>(data)); break;
                case ItemType::Consumable: 
                    playerInventory->addConsumable(std::make_unique<Consumable>(data)); break;
                default: return;
            }
            std::cout << "Bought " << data->name << " for " << data->price << " coins.\n";
        }
};
