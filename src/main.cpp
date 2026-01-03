// Custom Includes
#include "Architecture/Game.hpp"
#include "textures.hpp"
#include "audio.hpp"

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// Standard Libraries
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <filesystem>

int main() // main function, where the flow of the game starts
{
    std::srand(static_cast<unsigned>(std::time(nullptr))); // seed random number generator

    loadTextures(); // load game textures
    loadAudio(); // load game audio

    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "Croupier", sf::Style::Default); // declare window
    window.setFramerateLimit(60); // set fps limit to avoid too much GPU stress

    sf::Image icon;
    icon.loadFromFile("textures/Icons/Croupier.png");
    window.setIcon(
        icon.getSize().x,
        icon.getSize().y,
        icon.getPixelsPtr()
    );

    Game game(window); // declare Game object, which manages the overall game flow and StateManager
    game.run(); // run the game, which starts the game loop inside Game class

    return 0; // return 0 to finish the main function when the game is quit
}