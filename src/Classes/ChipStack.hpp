#pragma once

// Custom Includes
#include "Chip.hpp"

// SFML
#include <SFML/Graphics.hpp>

// Standard Libraries
#include <iostream>
#include <vector>

class ChipStack : public sf::Drawable
{
    private:
        std::vector<std::unique_ptr<Chip>> chips;

        sf::Vector2f position;
        float verticalOffset = 16.f;

        bool bettingEnabled = true;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
            for (auto& chip : chips)
                target.draw(*chip);
        }
    public:
        ChipStack(sf::Vector2f pos)
        {
            position = pos;
        }
        std::vector<std::unique_ptr<Chip>>& getChips() { return chips; }
        float getVerticalOffset() { return verticalOffset; }
        void setBettingEnabled(bool enabled)
        {
            bettingEnabled = enabled;

            if (!bettingEnabled) { updateStackPositions(); }
        }
        void addChip(sf::Sprite sprite)
        {
            auto chip = std::make_unique<Chip>(sprite);
            chips.push_back(std::move(chip));
            updateStackPositions();
        }
        void updateStackPositions()
        {
            for (int i = 0; i < chips.size(); ++i)
            {
                sf::Vector2f pos = position;
                pos.y -= i * verticalOffset;

                chips[i]->setPosition(pos);
                chips[i]->setSnapPosition(pos);
            }
        }
        std::vector<std::unique_ptr<Chip>> takeChips(int index)
        {
            std::vector<std::unique_ptr<Chip>> taken;

            if (index < 0 || index >= chips.size())
                return taken;

            for (int i = chips.size() - 1; i >= index; --i)
            {
                taken.push_back(std::move(chips.back()));
                chips.pop_back();
            }

            updateStackPositions();
            return taken;
        }
        void returnChips(std::vector<std::unique_ptr<Chip>>& returned)
        {
            for (auto& chip : returned)
            {
                chips.push_back(std::move(chip));
            }
            returned.clear();
            updateStackPositions();
        }
        int getClickedChipIndex(sf::Vector2f mousePos)
        {
            for (int i = chips.size() - 1; i >= 0; --i)
            {
                if (chips[i]->isMouseOver(mousePos.x, mousePos.y)) { return i; }
            }
            return -1;
        }
};