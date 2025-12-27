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

#ifdef _WIN32
#include <windows.h>
#endif

int main() // main function, where the flow of the game starts
{
    std::filesystem::path exePath = std::filesystem::current_path();

    #ifdef _WIN32
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        exePath = std::filesystem::path(buffer).parent_path().parent_path();
    #endif

    std::filesystem::current_path(exePath);
    std::cout << "Working directory set to: " << std::filesystem::current_path() << "\n";

    std::srand(static_cast<unsigned>(std::time(nullptr))); // seed random number generator

    loadTextures(); // load game textures
    loadAudio(); // load game audio

    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "BaccaratProject", sf::Style::Close); // declare window
    window.setFramerateLimit(60); // set fps limit to avoid too much GPU stress

    Game game(window); // declare Game object, which manages the overall game flow and StateManager
    game.run(); // run the game, which starts the game loop inside Game class

    return 0; // return 0 to finish the main function when the game is quit
}