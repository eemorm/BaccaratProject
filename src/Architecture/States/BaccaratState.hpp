#pragma once

// Custom Includes
#include "../GameState.hpp"
#include "../../Classes/Card.hpp"
#include "../../Classes/ChipStack.hpp"
#include "../../Classes/Interfaces/IObjectAction.hpp"
#include "../../Classes/LightSystem.hpp"

// SFML
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// Standard Libraries
#include <iostream>
#include <vector>

class BaccaratState : public GameState
{
    private:
        sf::RenderWindow& window;

        LightSystem lighting; // declare LightSystem
        sf::RenderTexture lightingRT;
        sf::RenderTexture worldRT;
        sf::RenderTexture ditherRT;

        std::vector<IObjectAction*> clickables; // declare clickables array to store references to clickable objects

        // ---DECLARE OBJECTS FOR TESTING---
        Card card;
        ChipStack bankStack;
        sf::Sprite table;

        sf::Vector2f mousePos;
        sf::Text cursorText;

    public:
        BaccaratState(sf::RenderWindow& w);

        void handleEvent(sf::Event& event) override;
        void update(float dt) override;
        void draw(sf::RenderWindow& window) override;
};
