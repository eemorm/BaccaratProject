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

        sf::Vector2f position;
        sf::Sprite chipSprite;

        std::vector<Chip> chips;
        std::vector<Chip> heldChips;
        int chipValue;

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
        ChipStack(sf::Vector2f p, int v, sf::Sprite s) : position(p), chipSprite(s), chipValue(v) { chipSprite.setScale(3, 3); }
        std::vector<Chip>& getChips() { return chips; }
        std::vector<Chip>& getHeldChips() { return heldChips; }
        int getChipValue() { return chipValue; }
        void setChipValue(int v) { chipValue = v; }
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
        void clear() { chips.clear(); heldChips.clear(); }
        void addChip(sf::Sprite sprite)
        {
            Chip chip;
            chip.sprite = chipSprite;
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
        sf::FloatRect getPickupBounds(sf::Sprite sprite)
        {
            sf::FloatRect spriteBounds = sprite.getGlobalBounds();

            float pickupHeight = 53.f;
            return sf::FloatRect(
                spriteBounds.left,
                spriteBounds.top + spriteBounds.height - pickupHeight,
                spriteBounds.width,
                pickupHeight
            );
        }
        int getClickedChipIndex(sf::Vector2f mousePos)
        {
            if (chips.empty()) return -1;

            for (int i = chips.size() - 1; i >= 0; --i)
            {
                if (getPickupBounds(chips[i].sprite).contains(mousePos))
                    return i;
            }

            return -1;
        }
        void acceptBet() { heldChips.clear(); isDragging = false; }
        bool isMouseOver(float x, float y) override
        {
            for (int i = chips.size() - 1; i >= 0; --i)
            {
                if (getPickupBounds(chips[i].sprite).contains(x, y))
                    return true;
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