#pragma once

// SFML
#include <SFML/Graphics.hpp>

/*
    class GameState

    Base class for all game states in the application.
    Provides a common interface for handleEvent, update, and draw.
    GameStates are managed by the GameStateManager, which switches between different states as needed, using pointers to this class.
*/
class GameState
{
    public:
        virtual ~GameState() {} // virtual destructor for proper cleanup of derived classes
        virtual void handleEvent(sf::Event& event) {} // virtual method to be overridden by derived classes for event handling
        virtual void update(float dt) {} // virtual method to be overridden by derived classes for updating game logic and visuals
        virtual void draw(sf::RenderWindow& window) {} // virtual method to be overridden by derived classes for rendering to the window
};