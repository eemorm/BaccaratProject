#pragma once

// SFML
#include <SFML/Graphics.hpp>

// defines an object as actionable, methods for executing actions
class IObjectAction
{
    public:
        IObjectAction() {}
        ~IObjectAction() {}
        virtual bool isMouseOver(float mx, float my) { return false; }
        virtual void onClick() {}
        virtual void onMoveStart(sf::Vector2f mousePos) {}
        virtual void onMove(sf::Vector2f mousePos) {}
        virtual void onMoveEnd(sf::Vector2f mousePos) {}
};