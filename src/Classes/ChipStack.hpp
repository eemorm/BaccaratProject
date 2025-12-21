#pragma once

// Custom Includes
#include "../textures.hpp"

// SFML
#include <SFML/Graphics.hpp>

// Standard Libraries
#include <iostream>
#include <vector>

class ChipStack : public sf::Drawable, public IObjectAction
{
    private:
        struct Chip
        {
            sf::Sprite sprite;
            sf::Vector2f offset;
            sf::Vector2f targetPosition;
            int originalIndex = -1;
            bool returning = false;
        };

        std::vector<Chip> chips;
        std::vector<Chip> heldChips;

        sf::Vector2f position;
        float verticalOffset = 16.f;
        bool isDragging = false;
        int grabbedIndex = -1;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
            for (const auto& chip : chips)
                target.draw(chip.sprite);

            for (const auto& chip : heldChips)
                target.draw(chip.sprite);
        }
    public:
        ChipStack(sf::Vector2f pos)
        {
            position = pos;
        }
        std::vector<Chip>& getChips() { return chips; }
        std::vector<Chip>& getHeldChips() { return heldChips; }
        sf::Vector2f getPosition() { return position; }      
        void setPosition(sf::Vector2f p) { position = p; }  
        float getVerticalOffset() { return verticalOffset; }
        void setVerticalOffset(float vo) { verticalOffset = vo; }
        sf::Vector2f computePosition(int index) { return { position.x, position.y - index * verticalOffset }; }
        void updateStackPositions()
        {
            for (int i = 0; i < chips.size(); ++i)
            {
                sf::Vector2f pos = position;
                pos.y -= i * verticalOffset;

                chips[i].sprite.setPosition(pos);
            }
        }
        void addChip(sf::Sprite sprite)
        {
            Chip chip;
            chip.sprite = theDealerBackground;
            chips.push_back(chip);
            updateStackPositions();
        }
        std::vector<Chip> takeChips(int index)
        {
            std::vector<Chip> taken;

            for (int i = index; i < chips.size(); ++i)
                taken.push_back(chips[i]);

            chips.erase(chips.begin() + index, chips.end());
            updateStackPositions();

            return taken;
        }
        void returnChips(std::vector<Chip>& returned)
        {
            for (auto chip : returned)
            {
                chips.push_back(chip);
            }
            returned.clear();
            updateStackPositions();
        }
        int getClickedChipIndex(sf::Vector2f mousePos)
        {
            if (chips.empty()) return -1;

            for (int i = chips.size() - 1; i >= 0; --i)
                if (chips[i].sprite.getGlobalBounds().contains(mousePos))
                    return i;

            return -1;
        }
        bool isMouseOver(float x, float y) override
        {
            for (auto i = 0; i < chips.size(); i++)
            {
                if (chips[i].sprite.getGlobalBounds().contains(x, y)) { return chips[i].sprite.getGlobalBounds().contains(x, y); }
            }
            return false;
        }
        void onMoveStart(sf::Vector2f mousePos) override
        {
            if (isDragging) return;

            int index = getClickedChipIndex(mousePos);
            if (index == -1) return;

            isDragging = true;
            grabbedIndex = index;

            heldChips = takeChips(index);

            for (int i = 0; i < heldChips.size(); ++i)
            {
                heldChips[i].offset = heldChips[i].sprite.getPosition() - mousePos;
            }
        }
        void onMove(sf::Vector2f mousePos) override
        {
            if (!isDragging) return;

            for (int i = 0; i < heldChips.size(); ++i)
            {
                sf::Vector2f pos = mousePos + heldChips[i].offset;
                heldChips[i].sprite.setPosition(pos);
            }
        }
        void onMoveEnd(sf::Vector2f mousePos) override
        {
            if (!isDragging) return;
            isDragging = false;

            int baseIndex = chips.size();

            for (int i = 0; i < heldChips.size(); ++i)
            {
                sf::Vector2f target = position;
                target.y -= (baseIndex + i) * verticalOffset;
                heldChips[i].targetPosition = target;
            }
        }
        void update(float dt)
        {
            if (!isDragging && !heldChips.empty())
            {
                float lerpSpeed = 10.f;

                for (int i = 0; i < heldChips.size(); ++i)
                {
                    sf::Vector2f current = heldChips[i].sprite.getPosition();
                    sf::Vector2f target = heldChips[i].targetPosition;

                    sf::Vector2f newPos = current + (target - current) * lerpSpeed * dt;
                    heldChips[i].sprite.setPosition(newPos);
                }

                bool allAtTarget = true;
                for (auto& chip : heldChips)
                {
                    if (std::abs(chip.sprite.getPosition().y - chip.targetPosition.y) > 0.5f)
                        allAtTarget = false;
                }

                if (allAtTarget)
                {
                    for (auto& chip : heldChips)
                        chips.push_back(chip);

                    heldChips.clear();
                    updateStackPositions();
                }
            }
        }
};