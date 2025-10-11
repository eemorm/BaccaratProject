#include "textures.hpp"
#include "Classes/Card.hpp"

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

    window.setFramerateLimit(60); // set fps limit to avoid too much GPU stress

    loadTextures(); // load game textures

    while (window.isOpen()) // loop when the window is open
    {
        sf::Event event; // declare an event for when an event happens
        
        while (window.pollEvent(event)) // check if window events pressed, i.e. close window
        {
            if (event.type == sf::Event::Closed) // check if window close pressed
            {
                window.close(); // close window
            }      
        }

        window.clear(sf::Color::Black); // clear window

        window.display(); // display output
    }
    
    return 0; // return 0 to finish the main function when the game is quit
}