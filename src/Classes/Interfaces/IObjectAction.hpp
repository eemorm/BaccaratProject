#pragma once

// SFML
#include <SFML/Graphics.hpp>

/*
    class IObject Action

    Defines an object as actionable, and contains methods for executing actions.
    Used to manage object clicking and movement in a modular way.
    Used by having a class inherit from IObjectAction.
*/
class IObjectAction
{
    public:
        IObjectAction() {}
        ~IObjectAction() {}
        virtual bool isMouseOver(float mx, float my) { return false; } // returns if the mouse if over a specific location
        virtual void onClick() {} // captures a click and executes action on click
        virtual void onMoveStart(sf::Vector2f mousePos) {} // executes when an object is picked up or moved
        virtual void onMove(sf::Vector2f mousePos) {} // executes during when an object is picked up or moved
        virtual void onMoveEnd(sf::Vector2f mousePos) {} // executes as an object is done being moved or being put down
};