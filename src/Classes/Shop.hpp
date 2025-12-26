#pragma once

// Custom Includes
#include "Inventory.hpp"
#include "WealthManager.hpp"
#include "../UI/Elements/UIButton.hpp"

// SFML
#include <SFML/Graphics.hpp>

// Standard Libraries
#include <iostream>
#include <string>
#include <memory>

class Shop : public sf::Drawable
{
    private:
        std::vector<ItemData*> availableItems;
        Inventory* playerInventory;
        WealthManager* chipWealthManager;

        //---UI---
        UIButton shopButton;
        bool shopOpen = false;
        float slotSize = 80;
        float padding = 10;
        int hoveredIndex = -1;
        bool isHovering = false;
    public:
        Shop(Inventory* inv, WealthManager* cwm) :
            playerInventory(inv),
            chipWealthManager(cwm),
            shopButton(
                sf::Vector2f(1146, 150),
                sf::Vector2f(200, 50),
                "Shop",
                font,
                [this]() {
                    shopOpen = !shopOpen;
                }
            ) {}
        std::vector<ItemData*> getItems() { return availableItems; }
        bool getShopOpen() { return shopOpen; }
        void initializeShop() 
        {
            availableItems.push_back(&ItemDB::Dagger);
            availableItems.push_back(&ItemDB::Vest);
            availableItems.push_back(&ItemDB::Heal);
            availableItems.push_back(&ItemDB::Attack);
        }
        void addItem(ItemData* data) { availableItems.push_back(data); }
        void buyItem(int index) 
        {
            ItemData* data = availableItems[index];

            if(index < 0 || index >= availableItems.size()) return;
            if (chipWealthManager->getWealth() < data->price) return;
            if (playerInventory->getConsumables().size() >= playerInventory->getConsumablesLimit()) return;

            std::unique_ptr<Item> newItem;
            switch(data->type) 
            {
                case ItemType::Weapon: 
                    playerInventory->equipWeapon(std::make_unique<Item>(data)); break;
                case ItemType::Armor: 
                    playerInventory->equipArmor(std::make_unique<Item>(data)); break;
                case ItemType::Consumable: 
                    playerInventory->addConsumable(std::make_unique<Consumable>(data)); break;
                case ItemType::Attack:
                    playerInventory->addAttack(1); break;
                default: return;
            }
            std::cout << "Bought " << data->name << " for " << data->price << " coins.\n";
            chipWealthManager->addWealth(-(data->price));
            if (data->type != ItemType::Attack)
                availableItems.erase(availableItems.begin() + index);
            hoveredIndex = -1;
        }
        void handleEvent(sf::Event& event, sf::Vector2f mousePos) 
        {
            shopButton.handleEvent(event, mousePos);
            if (!shopOpen) return;

            hoveredIndex = -1;
            isHovering = false;

            for (size_t i = 0; i < availableItems.size(); i++)
            {
                sf::FloatRect slotBounds(
                    20 + i * (slotSize + padding),
                    20,
                    slotSize,
                    slotSize
                );

                if (slotBounds.contains(mousePos))
                {
                    hoveredIndex = static_cast<int>(i);
                    isHovering = true;
                    break;
                }
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                if (hoveredIndex != -1)
                {
                    buyItem(hoveredIndex);
                }
            }
        }
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
            if(shopOpen) 
            {
                sf::RectangleShape shopPanel;
                shopPanel.setSize({SCREEN_WIDTH, SCREEN_HEIGHT});
                shopPanel.setFillColor(sf::Color(50, 50, 50, 200));
                shopPanel.setPosition(0, 0);
                target.draw(shopPanel);

                for(size_t i = 0; i < availableItems.size(); i++) 
                {
                    sf::RectangleShape slot;
                    slot.setSize({slotSize, slotSize});
                    slot.setFillColor(sf::Color(100, 100, 100));
                    slot.setPosition(20 + i * (slotSize + padding), 20);
                    target.draw(slot);

                    sf::Sprite icon;
                    icon.setTexture(availableItems[i]->sprite);
                    icon.setPosition(slot.getPosition());
                    target.draw(icon);
                }

                if (hoveredIndex != -1 && isHovering)
                {
                    ItemData* item = availableItems[hoveredIndex];

                    sf::RectangleShape tooltip;
                    tooltip.setSize({300, 140});
                    tooltip.setFillColor(sf::Color(30, 30, 30, 220));
                    tooltip.setOutlineThickness(2);
                    tooltip.setOutlineColor(sf::Color::White);
                    tooltip.setPosition(20, 120);
                    target.draw(tooltip);

                    sf::Text name(item->name, font, 18);
                    name.setPosition(30, 130);
                    name.setFillColor(sf::Color::White);
                    target.draw(name);

                    sf::Text price("Price: $" + std::to_string(item->price), font, 14);
                    price.setPosition(30, 155);
                    target.draw(price);

                    sf::Text desc(item->description, font, 14);
                    desc.setPosition(30, 175);
                    desc.setLineSpacing(1.1f);
                    target.draw(desc);
                }
            }
            target.draw(shopButton);
        }
};
