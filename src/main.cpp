// Custom Includes
#include "textures.hpp"
#include "Classes/Card.hpp"
#include "Classes/Interfaces/IObjectAction.hpp"
#include "Classes/LightSystem.hpp"

// SFML
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// Standard Libraries
#include <iostream>
#include <vector>

// Screen Constants
const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;

int main() // main function, where the flow of the game starts
{
    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "BaccaratProject", sf::Style::Close); // declare window
    LightSystem lighting(SCREEN_WIDTH, SCREEN_HEIGHT);

    window.setFramerateLimit(60); // set fps limit to avoid too much GPU stress

    loadTextures(); // load game textures

    Card card(theDealerBackground, 
        theDealerNumbers[0], 
        theDealerSuits[0], 
        theDealerBackground, 
        sf::Color::White, 
        sf::Color::White, 
        sf::Color::White, 
        sf::Color::White);

    std::vector<IObjectAction*> clickables;

    card.setPosition({700, 400});
    clickables.push_back(&card);

    sf::Vector2f mousePos;

    lighting.addStaticLight(Light({700, 400}, 300.f, 1.0f, sf::Color::White));

    while (window.isOpen()) // loop when the window is open
    {
        sf::Event event; // declare an event for when an event happens
        
        while (window.pollEvent(event)) // check if window events pressed, i.e. close window
        {
            mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                for (auto* object : clickables)
                    if (object->isMouseOver(mousePos.x, mousePos.y))
                        object->onMoveStart(mousePos);
            }
            if (event.type == sf::Event::MouseMoved)
            {
                for (auto* object : clickables)
                    object->onMove(mousePos);
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                for (auto* object : clickables)
                    object->onMoveEnd(mousePos);
            }
            if (event.type == sf::Event::Closed) // check if window close pressed
            {
                window.close(); // close window
            }      
        }

        lighting.clearDynamicLights();
        lighting.addDynamicLight( Light(mousePos, 250.f, 1.0f, sf::Color::White) );

        lighting.update();
        window.clear(sf::Color::White); // clear window

        window.draw(lighting);
        window.draw(card);

        window.display(); // display output
    }
    
    return 0; // return 0 to finish the main function when the game is quit
}