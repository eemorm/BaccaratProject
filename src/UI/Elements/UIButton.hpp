#pragma once

// Custom Includes
#include "../UIElement.hpp"

// SFML
#include <SFML/Graphics.hpp>

// Standard Libraries
#include <functional>
#include <string>

struct UIButtonStyle 
{
    sf::Color backgroundColor = sf::Color(80, 80, 80);
    sf::Color hoverColor      = sf::Color(120, 120, 120);
    sf::Color textColor       = sf::Color::White;

    int textSize              = 24;
    sf::Vector2f padding      = {10.f, 5.f};
};

class UIButton : public UIElement 
{
    private:
        sf::RectangleShape box;
        sf::Text label;
        UIButtonStyle style;
        std::function<void()> onClick;
        bool hovered = false;
    public:
        UIButton(
            sf::Vector2f pos,
            sf::Vector2f size,
            const std::string& text,
            sf::Font& font,
            std::function<void()> callback,
            UIButtonStyle style = {}
        )
        : style(style), onClick(callback)
        {
            box.setPosition(pos);
            box.setSize(size);
            box.setFillColor(style.backgroundColor);

            label.setFont(font);
            label.setString(text);
            label.setCharacterSize(style.textSize);
            label.setFillColor(style.textColor);
            label.setPosition(pos + style.padding);
        }
        void handleEvent(sf::Event& event, sf::Vector2f& mouse) override 
        {
            hovered = box.getGlobalBounds().contains(mouse);
            box.setFillColor(hovered ? style.hoverColor : style.backgroundColor);
            if (hovered &&
                event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                onClick();
            }
        }
        void draw(sf::RenderTarget& target) override 
        {
            target.draw(box);
            target.draw(label);
        }
};
