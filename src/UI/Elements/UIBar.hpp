#pragma once

// Custom Includes
#include "../UIElement.hpp"

// SFML
#include <SFML/Graphics.hpp>

// Standard Libraries
#include <algorithm>
#include <functional>
#include <string>

class UIBar : public UIElement 
{
    private:
        float value;
        float maxValue;
        sf::RectangleShape background;
        sf::RectangleShape bar;
        sf::Vector2f fullSize;
    public:
        UIBar(sf::Vector2f position, sf::Vector2f size, float max, sf::Color color) : value(max), maxValue(max)
        {
            fullSize = size;
            background.setSize(size);
            background.setFillColor(sf::Color(50, 50, 50));
            background.setPosition(position);

            bar.setSize(size);
            bar.setFillColor(color);
            bar.setPosition(position);
        }
        void handleEvent(sf::Event& e, sf::Vector2f& mouse) override {}
        void updateBar(float currentValue)
        {
            value = std::max(currentValue, 0.f);
            bar.setSize({(value/maxValue) * fullSize.x, fullSize.y});
        }
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override 
        {
            target.draw(background);
            target.draw(bar);
        }
};
