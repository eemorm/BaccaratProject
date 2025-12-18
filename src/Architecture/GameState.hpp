#pragma once

// SFML
#include <SFML/Graphics.hpp>

class GameState
{
    public:
        virtual ~GameState() {}

        virtual void handleEvent(sf::Event& event) {}
        virtual void update(float dt) {}
        virtual void draw(sf::RenderWindow& window) {}
};