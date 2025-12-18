#pragma once

// SFML
#include <SFML/Graphics.hpp>

// Custom Includes
#include "../GameState.hpp"

class BaccaratState : public GameState
{
    private:
        sf::RenderWindow& window;

        //ChipStack bankStack;
        //HeldChips held;   (we add next)

    public:
        BaccaratState(sf::RenderWindow& w) : window(w) {}

        void handleEvent(sf::Event& event) override;
        void update(float dt) override;
        void draw(sf::RenderWindow& window) override;
};
