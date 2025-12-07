#pragma once

// Custom Includes
#include "Interfaces/IObjectAction.hpp"

// SFML
#include <SFML/Graphics.hpp>

// Standard Libraries
#include <iostream>

class Chip : public sf::Drawable, public IObjectAction
{
    private:
        sf::Sprite sprite;
        bool isMoving = false;
        sf::Vector2f offset;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override 
        {
            target.draw(sprite);
        }
    public:
        Chip(sf::Sprite s)
        {
            sprite = s;
        }

        void setPosition(sf::Vector2f pos) { sprite.setPosition(pos); }
        sf::Vector2f getPosition() { return sprite.getPosition(); }

        bool isMouseOver(float x, float y) override
        {
            return sprite.getGlobalBounds().contains(x, y);
        }
        void onMoveStart(sf::Vector2f mousePos) override
        {
            if (sprite.getGlobalBounds().contains(mousePos))
            {
                isMoving = true;
                offset = sprite.getPosition() - mousePos;
            }
        }
        void onMove(sf::Vector2f mousePos) override
        {
            if (isMoving)
                sprite.setPosition(mousePos + offset);
        }
        void onMoveEnd(sf::Vector2f mousePos) override
        {
            isMoving = false;
        }
};