#pragma once

// Custom Includes
#include "../UIElement.hpp"

// SFML
#include <SFML/Graphics.hpp>

// Standard Libraries
#include <functional>
#include <string>

class HealthBar : public UIElement 
{
    private:
        float value;
        float maxValue;
        sf::RectangleShape background;
        sf::RectangleShape bar;
        sf::Vector2f fullSize;
    public:
        HealthBar(sf::Vector2f position, sf::Vector2f size, float max)
            : maxValue(max), currentValue(max)
        {
            size = size
            background.setSize(size);
            background.setFillColor(sf::Color(50, 50, 50));
            background.setPosition(position);

            bar.setSize(size);
            bar.setFillColor(sf::Color::Red);
            bar.setPosition(position);
        }
        void handleEvent(sf::Event& e, sf::Vector2f& mouse) override {}
        void update(float dt, float currentValue) override 
        {
            value = currentValue;
            background.setSize({(value/maxValue) * fullSize.x, fullSize.y});
        }
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {}
};
