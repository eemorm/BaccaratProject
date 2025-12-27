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
    #ifdef _WIN32
        // Change working directory to project root (assumes executable is in build/)
        fs::path exePath = fs::current_path();      // e.g., build/
        fs::path projectRoot = exePath.parent_path(); // go up one level to project root
        fs::current_path(projectRoot);

        std::cout << "Windows working directory set to project root: " 
                  << fs::current_path() << "\n";
    #endif

    std::srand(static_cast<unsigned>(std::time(nullptr))); // seed random number generator

    loadTextures(); // load game textures
    loadAudio(); // load game audio

    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "BaccaratProject", sf::Style::Close); // declare window
    window.setFramerateLimit(60); // set fps limit to avoid too much GPU stress

    Game game(window); // declare Game object, which manages the overall game flow and StateManager
    game.run(); // run the game, which starts the game loop inside Game class

    return 0; // return 0 to finish the main function when the game is quit
}