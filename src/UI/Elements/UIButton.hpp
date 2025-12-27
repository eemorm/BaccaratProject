#pragma once

// Custom Includes
#include "../../audio.hpp"
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
        std::function<void()> onClick;
        UIButtonStyle style;
        bool hovered = false;
        bool active = true;
    public:
        UIButton(
            sf::Vector2f pos,
            sf::Vector2f size,
            const std::string& text,
            sf::Font& font,
            std::function<void()> callback,
            UIButtonStyle style = {},
            bool active = true
        )
        : onClick(callback), style(style), active(active)
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
        bool getActive() { return active; }
        void setActive(bool a) { active = a; }
        void handleEvent(sf::Event& event, sf::Vector2f& mouse) override 
        {
            if (!active) return;

            hovered = box.getGlobalBounds().contains(mouse);
            box.setFillColor(hovered ? style.hoverColor : style.backgroundColor);
            if (hovered &&
                event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                onClick();
            }
        }
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override 
        {
            if (!active) return;
            target.draw(box, states);
            target.draw(label, states);
        }
        void setOnClick(std::function<void()> callback) { onClick = callback; }
};
