#pragma once

// SFML
#include "GameState.hpp"

// Standard IO
#include <memory>

/*
    class GameStateManager

    Manages game states such as BaccaratState by holding a pointer to the current state.
    By holding a pointer to the base class GameState, it can manage any derived state class polymorphically, and call the appropriate overridden methods.
    Also used to switch between different game states by changing the pointer to a different reference to a derived GameState class.
*/
class GameStateManager
{
    private:
        std::unique_ptr<GameState> currentState; // keep reference to current game state
    public:
        void setState(std::unique_ptr<GameState> state) { currentState = std::move(state); } // change state in the manager
        void handleEvent(sf::Event& event) { if (currentState) currentState->handleEvent(event); } // pass event to current state to handle, handle event through a pointer to have polymorphism
        void update(float dt) { if (currentState) currentState->update(dt); } // update current state with respect to delta time, update through a pointer to have polymorphism
        void draw(sf::RenderWindow& window) { if (currentState) currentState->draw(window);} // draw current state to window, draw through a pointer to have polymorphism
        /* NOTE: for reference, the pointer is to a GameState, but the actual object is a derived class of GameState such as BaccaratState. This allows for polymorphism,
        meaning that the correct overridden methods in the derived class are called instead of the base class methods. */
};
