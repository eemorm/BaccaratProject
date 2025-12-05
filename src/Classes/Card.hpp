#pragma once

// Custom Includes
#include "Interfaces/IObjectAction.hpp"

// SFML
#include <SFML/Graphics.hpp>

// Standard Libraries
#include <iostream>

class Card : public sf::Drawable, public IObjectAction
{
    private:
        bool show = true;
    
        sf::Transformable transform;

        sf::Sprite background;
        sf::Sprite number;
        sf::Sprite suit;
        sf::Sprite backside;
        sf::Color backgroundColor;
        sf::Color numberColor;
        sf::Color suitColor;
        sf::Color backsideColor;

        sf::Vector2f position;
        float rotation;
        float scale;

        bool isMoving = false;
        sf::Vector2f moveOffset;
        float moveRotation = 0.0f;
        sf::Vector2f prevMousePos;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override 
        {
            states.transform *= transform.getTransform();

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

            background.setPosition({0.f, 0.f});
            number.setPosition({64.f, 2.f});
            suit.setPosition({34.f, 43.f});
            backside.setPosition({0.f, 0.f});

            transform.setPosition({0.f, 0.f});
            transform.setRotation(0.f);
            transform.setScale({1.f, 1.f});

            sf::FloatRect b = background.getLocalBounds();
            transform.setOrigin(b.width / 2.f, b.height / 2.f);

            position = transform.getPosition();
        }
        void setPosition(sf::Vector2f pos) { transform.setPosition(pos); position = pos; }
        void setRotation(float rot) { transform.setRotation(rot); rotation = rot; }
        void setScale(float scl) { transform.setScale({scl, scl}); scale = scl; }
        void flip() { show = !show; }
        bool isMouseOver(float mx, float my) override
        {
            sf::FloatRect localCoordinates = background.getLocalBounds();
            sf::FloatRect worldCoordinates = transform.getTransform().transformRect(localCoordinates);

            return worldCoordinates.contains(mx, my);
        }
        void onMoveStart(sf::Vector2f mousePos) override
        {
            isMoving = true;
            moveOffset = position - mousePos;
            prevMousePos = mousePos;
            setScale(1.1f);
        }
        void onMove(sf::Vector2f mousePos) override
        {
            if (!isMoving) { return; }

            setPosition(mousePos + moveOffset);

            sf::Vector2f delta = mousePos - prevMousePos;
            moveRotation = delta.x * 0.2f;

            setRotation(moveRotation);

            prevMousePos = mousePos;
        }
        void onMoveEnd(sf::Vector2f mousePos) override
        {
            isMoving = false;
            setRotation(0);
            setScale(1.0f);
        }
};