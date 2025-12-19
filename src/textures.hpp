#pragma once

// SFML
#include <SFML/Graphics.hpp>

// Standard Libraries
#include <iostream>
#include <vector>

// ---SCREEN CONSTANTS---
extern const unsigned int SCREEN_WIDTH;
extern const unsigned int SCREEN_HEIGHT;

// ---TEXTURES FOR SPRITES---
extern sf::Texture tableTexture;
extern sf::Texture theDealerBackgroundTexture;
extern sf::Texture theDealerNumbersTexture;
extern sf::Texture theDealerSuitsTexture;

// ---SPRITES---
extern sf::Sprite table;
extern sf::Sprite theDealerBackground;
extern std::vector<sf::Sprite> theDealerNumbers;
extern std::vector<sf::Sprite> theDealerSuits;

// ---SHADERS---
extern sf::Shader ditherShader;
extern sf::Shader pixelationShader;

//---FONTS---
extern sf::Font font;

void splitTextures(sf::Texture* texture, int sections, std::vector<sf::Sprite>* destination, float size);
void loadTextures();