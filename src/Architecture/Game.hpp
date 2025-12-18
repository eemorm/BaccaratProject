#pragma once

// Custom Includes
#include "GameStateManager.hpp"
#include "States/BaccaratState.hpp"

// SFML
#include <SFML/Graphics.hpp>

class Game
{
    private:
        sf::RenderWindow& window;
        GameStateManager states;
        sf::Clock clock;
    public:
        Game(sf::RenderWindow& w) : window(w)
        {
            states.setState(std::make_unique<BaccaratState>(window));
        }
        void run()
        {
            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();

                    states.handleEvent(event);
                }

                float dt = clock.restart().asSeconds();

                states.update(dt);

                window.clear();
                states.draw(window);
                window.display();
            }
        }
};
