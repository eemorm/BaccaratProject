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

        sf::Vector2f snapPosition;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override 
        {
            target.draw(sprite);
        }
    public:
        Chip(sf::Sprite s)
        {
            sprite = s;
            snapPosition = sprite.getPosition();
        }
        void setPosition(sf::Vector2f p) { sprite.setPosition(p); }
        sf::Vector2f getPosition() { return sprite.getPosition(); }
        void setSnapPosition(sf::Vector2f p) { snapPosition = p; }
        sf::Vector2f getOffset() { return offset; }
        void setOffset(sf::Vector2f o) { offset = o; }
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