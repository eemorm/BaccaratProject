// Custom Includes
#include "textures.hpp"

// SFML
#include <SFML/Graphics.hpp>

// Standard Libraries
#include <iostream>
#include <vector>

// ---SCREEN CONSTANTS---
const unsigned int SCREEN_WIDTH = 1366;
const unsigned int SCREEN_HEIGHT = 768;

// ---TEXTURES FOR SPRITES---
sf::Texture tableTexture;
sf::Texture theDealerBackgroundTexture;
sf::Texture theDealerNumbersTexture;
sf::Texture theDealerSuitsTexture;

// ---SPRITES---
sf::Sprite table;
sf::Sprite theDealerBackground;
std::vector<sf::Sprite> theDealerNumbers;
std::vector<sf::Sprite> theDealerSuits;

// ---SHADERS---
sf::Shader ditherShader;
sf::Shader pixelationShader;

//---FONTS---
sf::Font font;

void splitTextures(sf::Texture* texture, int sections, std::vector<sf::Sprite>* destination, float size) // splits textures that are in sections
{
    for (int i = 0; i < sections; i++)
    {
        sf::Sprite sprite;
        sprite.setTexture(*texture);

        sprite.setTextureRect(sf::IntRect(i * size, 0, size, size));

        destination->push_back(sprite);
    }
}

void loadTextures() // loads textures, used at start of game, puts textures into referenceble sprites
{
    float bits = 32.0;

    // ---LOAD TEXTURES---
    if (!tableTexture.loadFromFile("textures/Core/table.png")) 
    { std::cout << "Failed to load sprite sheet!\n"; }
    if (!theDealerBackgroundTexture.loadFromFile("textures/Cards/TheDealer/TheDealerBackground.png")) 
    { std::cout << "Failed to load sprite sheet!\n"; }
    if (!theDealerNumbersTexture.loadFromFile("textures/Cards/TheDealer/TheDealerNumbers.png")) 
    { std::cout << "Failed to load sprite sheet!\n"; }
    if (!theDealerSuitsTexture.loadFromFile("textures/Cards/TheDealer/TheDealerSuits.png")) 
    { std::cout << "Failed to load sprite sheet!\n"; }

    // ---SET TEXTURES INTO SPRITES---
    table.setTexture(tableTexture);
    theDealerBackground.setTexture(theDealerBackgroundTexture);
    splitTextures(&theDealerNumbersTexture, 9, &theDealerNumbers, bits);
    splitTextures(&theDealerSuitsTexture, 4, &theDealerSuits, bits);

    // ---LOAD SHADERS---
    if (!ditherShader.loadFromFile("shaders/dither.frag", sf::Shader::Fragment))
    { std::cerr << "Failed to load shader\n"; }
    if (!pixelationShader.loadFromFile("shaders/pixelation.frag", sf::Shader::Fragment))
    { std::cerr << "Failed to load shader\n"; }

    // ---LOAD FONTS---
    if (!font.loadFromFile("fonts/sharetech.ttf")) 
    { std::cerr << "Failed to load font\n"; }
}