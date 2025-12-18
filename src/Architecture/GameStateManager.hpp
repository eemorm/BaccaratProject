#pragma once

// SFML
#include "GameState.hpp"

// Standard IO
#include <memory>

class GameStateManager
{
    private:
        std::unique_ptr<GameState> currentState;

    public:
        void setState(std::unique_ptr<GameState> state)
        {
            currentState = std::move(state);
        }

        void handleEvent(sf::Event& event)
        {
            if (currentState) currentState->handleEvent(event);
        }

        void update(float dt)
        {
            if (currentState) currentState->update(dt);
        }

        void draw(sf::RenderWindow& window)
        {
            if (currentState) currentState->draw(window);
        }
};
