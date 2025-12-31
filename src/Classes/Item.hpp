#pragma once

// Custom Includes
#include "PlayerHealth.hpp"

// SFML
#include <SFML/Graphics.hpp>

// Standard Libraries
#include <string>

enum class ItemType { Weapon, Armor, Consumable, Attack };
struct ItemData 
{
    std::string name;
    std::string description;
    int price;
    ItemType type;
    sf::Texture sprite;
    int damage;
    int armorValue;
    int heal;
    int minFloor;
};
class Item 
{
    protected:
        ItemData* data;
    public:
        Item(ItemData* d) : data(d) {}
        virtual ~Item() {}

        ItemData* getData() { return data; }
        virtual void use(PlayerHealth& player) {}
};
class Consumable : public Item
{
    public:
        Consumable(ItemData* d) : Item(d) {}
        void use(PlayerHealth& player) override
        {
            player.heal(data->heal);
        }
};
