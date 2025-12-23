#pragma once

// SFML
#include <SFML/Graphics.hpp>

// Standard Libraries
#include <string>

enum class ItemType { Weapon, Armor, Consumable };
struct ItemData 
{
    std::string name;
    int price;
    ItemType type;
    sf::Texture sprite;
    int damage;
    int armorValue;
};
class Item 
{
    protected:
        ItemData* data;
    public:
        Item(ItemData* d) : data(d) {}
        virtual ~Item() {}

        ItemData* getData() { return data; }
        virtual void use() {}
};
class Consumable : public Item 
{
    public:
        Consumable(ItemData* d) : Item(d) {}
        void use() override
        {
            std::cout << "Used consumable:  " << data->name << "\n";
        }
};
