#pragma once

// SFML
#include <SFML/Graphics.hpp>

//Standard Libraries
#include <iostream>
#include <vector>

sf::Texture theDealerBackgroundTexture;
sf::Texture theDealerNumbersTexture;
sf::Texture theDealerSuitsTexture;

sf::Sprite theDealerBackground;
std::vector<sf::Sprite> theDealerNumbers;
std::vector<sf::Sprite> theDealerSuits;

void splitTextures(sf::Texture* texture, int sections, std::vector<sf::Sprite>* destination, float size)
{
    for (int i = 0; i < sections; i++)
    {
        sf::Sprite sprite;
        sprite.setTexture(*texture);

        sprite.setTextureRect(sf::IntRect(i * size, 0, size, size));

        destination->push_back(sprite);
    }
}

void loadTextures()
{
    float bits = 32.0;

    if (!theDealerBackgroundTexture.loadFromFile("textures/Cards/TheDealer/TheDealerBackground.png")) 
    { std::cout << "Failed to load sprite sheet!\n"; }
    if (!theDealerNumbersTexture.loadFromFile("textures/Cards/TheDealer/TheDealerNumbers.png")) 
    { std::cout << "Failed to load sprite sheet!\n"; }
    if (!theDealerSuitsTexture.loadFromFile("textures/Cards/TheDealer/TheDealerSuits.png")) 
    { std::cout << "Failed to load sprite sheet!\n"; }

    theDealerBackground.setTexture(theDealerBackgroundTexture);
    splitTextures(&theDealerNumbersTexture, 9, &theDealerNumbers, bits);
    splitTextures(&theDealerSuitsTexture, 4, &theDealerSuits, bits);
}