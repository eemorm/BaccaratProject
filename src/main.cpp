// Custom Includes
#include "Architecture/Game.hpp"
#include "textures.hpp"

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// Standard Libraries
#include <iostream>
#include <vector>

int main() // main function, where the flow of the game starts
{
    loadTextures(); // load game textures

    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "BaccaratProject", sf::Style::Close); // declare window
    window.setFramerateLimit(60); // set fps limit to avoid too much GPU stress

    Game game(window); // declare Game object, which manages the overall game flow and StateManager
    game.run(); // run the game, which starts the game loop inside Game class

    return 0; // return 0 to finish the main function when the game is quit
}