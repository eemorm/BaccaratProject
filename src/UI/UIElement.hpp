#pragma once

// SFML
#include <SFML/Graphics.hpp>

class UIElement : public sf::Drawable
{
    public:
        virtual ~UIElement() {};

        virtual void handleEvent(sf::Event& e, sf::Vector2f& mouse) {}
        virtual void update(float dt) {}
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {}
};