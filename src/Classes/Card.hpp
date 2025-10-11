#pragma once

// SFML
#include <SFML/Graphics.hpp>

// Standard Libraries
#include <iostream>

class Card : public sf::Drawable
{
    private:
        bool show = true;
    
        sf::Sprite background;
        sf::Sprite number;
        sf::Sprite suit;
        sf::Sprite backside;
        sf::Color backgroundColor;
        sf::Color numberColor;
        sf::Color suitColor;
        sf::Color backsideColor;

        sf::Vector2f position;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override 
        {
            if (!show)
            {
                target.draw(backside, states);
            }
            else 
            {
                target.draw(background, states);
                target.draw(number, states);
                target.draw(suit, states);
            }
        }
    public:
        Card(sf::Sprite bg, 
            sf::Sprite nm, 
            sf::Sprite st, 
            sf::Sprite bs, 
            sf::Color bgc, 
            sf::Color nmc, 
            sf::Color stc, 
            sf::Color bsc) 
        {
            background = bg;
            number = nm;
            suit = st;
            backside = bs;
            backgroundColor = bsc;
            numberColor = nmc;
            suitColor = stc;
            backsideColor = bsc;

            background.setColor(backgroundColor);
            number.setColor(numberColor);
            suit.setColor(suitColor);
            backside.setColor(backsideColor);
        }

        void flip() { show = !show; }

        void render(float x, float y)
        {
            position = {x, y};
            background.setPosition(position);
            number.setPosition(position.x + 64, position.y + 2);
            suit.setPosition(position.x + 34, position.y + 43);
            backside.setPosition(position);
        }
};