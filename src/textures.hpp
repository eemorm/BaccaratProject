#pragma once

// SFML
#include <SFML/Graphics.hpp>

// Standard Libraries
#include <iostream>
#include <vector>

/*
    textures.hpp

    Manages all textures and sprites used in the game.
    It provides functions to load textures from files, split sprite sheets into individual sprites.
    Centralizes texture and sprite management by acting as a "storage center".
    loadTextures() must be called at the start of the game to initialize assets.
*/

// ---SCREEN CONSTANTS---
const unsigned int SCREEN_WIDTH = 1366;
const unsigned int SCREEN_HEIGHT = 768;

// ---TEXTURES FOR SPRITES---
inline sf::Texture tableTexture;
inline sf::Texture theDealerBackgroundTexture;
inline sf::Texture theDealerNumbersTexture;
inline sf::Texture theDealerSuitsTexture;
inline sf::Texture theDealerTexture;
inline sf::Texture chipsTexture;
inline sf::Texture insectTexture;
inline sf::Texture ratTexture;
inline sf::Texture reaperTexture;
inline sf::Texture daggerTexture;
inline sf::Texture swordTexture;
inline sf::Texture throwingCardTexture;
inline sf::Texture vestTexture;
inline sf::Texture chainmailTexture;
inline sf::Texture bandageTexture;
inline sf::Texture potionTexture;
inline sf::Texture largePotionTexture;

// ---SPRITES---
inline sf::Sprite table;
inline sf::Sprite theDealerBackground;
inline std::vector<sf::Sprite> theDealerNumbers;
inline std::vector<sf::Sprite> theDealerSuits;
inline sf::Sprite theDealer;
inline std::vector<sf::Sprite> chips;

// ---SHADERS---
inline sf::Shader ditherShader;
inline sf::Shader pixelationShader;

//---FONTS---
inline sf::Font font;

inline void splitTextures(sf::Texture* texture, int sections, std::vector<sf::Sprite>* destination, float size) // splits textures that are in sections
{
    for (int i = 0; i < sections; i++) // for each section in the image
    {
        sf::Sprite sprite;
        sprite.setTexture(*texture); // take the reference to the texture and set it to the sprite

        sprite.setTextureRect(sf::IntRect(i * size, 0, size, size)); // set the texture rectangle to the section of the image (splice?)

        destination->push_back(sprite); // push back sprite to a vector for easy access, destination is a reference to a vector
    }
}

inline void loadTextures() // loads textures, used at start of game, puts textures into referenceble sprites
{
    float bits = 32.0; // size of each texture bit in the sprite sheets, which is used for splicing if needed

    // ---LOAD TEXTURES---
    if (!tableTexture.loadFromFile("textures/Core/table.png")) 
    { std::cout << "Failed to load sprite sheet!\n"; }
    if (!theDealerBackgroundTexture.loadFromFile("textures/Cards/TheDealer/TheDealerBackground.png")) 
    { std::cout << "Failed to load sprite sheet!\n"; }
    if (!theDealerNumbersTexture.loadFromFile("textures/Cards/TheDealer/TheDealerNumbers.png")) 
    { std::cout << "Failed to load sprite sheet!\n"; }
    if (!theDealerSuitsTexture.loadFromFile("textures/Cards/TheDealer/TheDealerSuits.png")) 
    { std::cout << "Failed to load sprite sheet!\n"; }
    if (!theDealerTexture.loadFromFile("textures/Dealers/theDealer.png")) 
    { std::cout << "Failed to load sprite sheet!\n"; }
    if (!chipsTexture.loadFromFile("textures/Core/chips.png")) 
    { std::cout << "Failed to load sprite sheet!\n"; }
    if (!insectTexture.loadFromFile("textures/Enemies/insect.png")) 
    { std::cout << "Failed to load sprite sheet!\n"; }
    if (!ratTexture.loadFromFile("textures/Enemies/rat.png")) 
    { std::cout << "Failed to load sprite sheet!\n"; }
    if (!reaperTexture.loadFromFile("textures/Enemies/reaper.png")) 
    { std::cout << "Failed to load sprite sheet!\n"; }
    if (!daggerTexture.loadFromFile("textures/Items/dagger.png")) 
    { std::cout << "Failed to load sprite sheet!\n"; }
    if (!swordTexture.loadFromFile("textures/Items/sword.png")) 
    { std::cout << "Failed to load sprite sheet!\n"; }
    if (!throwingCardTexture.loadFromFile("textures/Items/throwingcard.png")) 
    { std::cout << "Failed to load sprite sheet!\n"; }
    if (!vestTexture.loadFromFile("textures/Items/vest.png")) 
    { std::cout << "Failed to load sprite sheet!\n"; }
    if (!chainmailTexture.loadFromFile("textures/Items/chainmail.png")) 
    { std::cout << "Failed to load sprite sheet!\n"; } 
    if (!bandageTexture.loadFromFile("textures/Items/bandage.png")) 
    { std::cout << "Failed to load sprite sheet!\n"; }
    if (!potionTexture.loadFromFile("textures/Items/potion.png")) 
    { std::cout << "Failed to load sprite sheet!\n"; }
    if (!largePotionTexture.loadFromFile("textures/Items/largepotion.png")) 
    { std::cout << "Failed to load sprite sheet!\n"; }

    // ---SET TEXTURES INTO SPRITES---
    table.setTexture(tableTexture);
    theDealerBackground.setTexture(theDealerBackgroundTexture);
    splitTextures(&theDealerNumbersTexture, 13, &theDealerNumbers, bits);
    splitTextures(&theDealerSuitsTexture, 4, &theDealerSuits, bits);
    theDealer.setTexture(theDealerTexture);
    splitTextures(&chipsTexture, 4, &chips, bits);

    // ---LOAD SHADERS---
    if (!ditherShader.loadFromFile("shaders/dither.frag", sf::Shader::Fragment))
    { std::cerr << "Failed to load shader\n"; }
    if (!pixelationShader.loadFromFile("shaders/pixelation.frag", sf::Shader::Fragment))
    { std::cerr << "Failed to load shader\n"; }

    // ---LOAD FONTS---
    if (!font.loadFromFile("fonts/sharetech.ttf")) 
    { std::cerr << "Failed to load font\n"; }
}