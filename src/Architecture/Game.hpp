#pragma once

// Custom Includes
#include "GameStateManager.hpp"
#include "States/BaccaratState.hpp"
#include "States/MainMenuState.hpp"

// SFML
#include <SFML/Graphics.hpp>

/*
    class Game 

    Manages the main game loop, window, and game states.
    Uses GameStateManager to handle different game states such as menus and baccarat gameplay.
    Extracted from main.cpp for better organization in order to keep main.cpp clean and the project modular.
*/
class Game
{
    private:
        sf::RenderWindow& window; // window; comes from main.cpp; passed by reference for rendering
        GameStateManager states; // GameStateManager to handle different game states
        sf::Clock clock; // game clock for delta time calculation and timing in the game

        sf::Image icon;
        bool iconLoaded = false;
        bool iconSet = false;
    public:
        // constructor to initialize window and set initial game state
        Game(sf::RenderWindow& w) : window(w)
        {
            states.changeState(StateID::MainMenu, window);
        }
        void run() // main game loop, extracted from main.cpp for better organization
        {
            if (!iconLoaded)
            {
                iconLoaded = icon.loadFromFile("textures/Icons/Croupier.png");
            }

            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event)) // check for events
                {
                    if (event.type == sf::Event::Closed) // check if window close pressed
                    {
                        window.close(); // close window
                    }   

                    states.handleEvent(event); // handle event in current game state by passing event to GameStateManager to state, which will handle specific events
                }

                float dt = clock.restart().asSeconds(); // reset delta time clock for update

                states.update(dt); // update per frame with delta time through state

                window.clear(); // clear window for new frame
                states.draw(window); // draw frame to window
                window.display(); // display frame on window

                if (iconLoaded && !iconSet)
                {
                    window.setIcon(
                        icon.getSize().x,
                        icon.getSize().y,
                        icon.getPixelsPtr()
                    );
                    iconSet = true;
                }
            }
        }
};
