#pragma once

// Custom Includes
#include "Enemy.hpp"
#include "Card.hpp"

// SFML
#include <SFML/Graphics.hpp>

// Standard Libraries
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Dealer
{
    private:
        string name;
        vector<Enemy> enemies;
        sf::Sprite sprite;
        vector<Card> deck;
    public:

};