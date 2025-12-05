#pragma once

// SFML
#include <SFML/Graphics.hpp>

// defines an object as clickable
class IClickable
{
    public:
        IClickable() {}
        ~IClickable() {}
        virtual bool isMouseOver(float mx, float my) { return false; }
        virtual void onClick() {}
};