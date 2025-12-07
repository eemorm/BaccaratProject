// Custom Includes
#include "textures.hpp"
#include "Classes/Card.hpp"
#include "Classes/Chip.hpp"
#include "Classes/Interfaces/IObjectAction.hpp"
#include "Classes/LightSystem.hpp"

// SFML
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// Standard Libraries
#include <iostream>
#include <vector>

// Screen Constants
const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;

int main() // main function, where the flow of the game starts
{
    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "BaccaratProject", sf::Style::Close); // declare window
    LightSystem lighting(SCREEN_WIDTH, SCREEN_HEIGHT);

    window.setFramerateLimit(60); // set fps limit to avoid too much GPU stress

    loadTextures(); // load game textures

    sf::Shader ditherShader;
    if (!ditherShader.loadFromFile("shaders/dither.frag", sf::Shader::Fragment))
    {
        std::cerr << "Failed to load shader\n";
    }
    sf::Shader pixelationShader;
    if (!pixelationShader.loadFromFile("shaders/pixelation.frag", sf::Shader::Fragment))
    {
        std::cerr << "Failed to load shader\n";
    }

    sf::RenderTexture lightingRT;
    sf::RenderTexture worldRT;
    sf::RenderTexture ditherRT;

    lightingRT.create(SCREEN_WIDTH, SCREEN_HEIGHT);
    worldRT.create(SCREEN_WIDTH, SCREEN_HEIGHT);
    ditherRT.create(SCREEN_WIDTH, SCREEN_HEIGHT);

    sf::Sprite lightingSprite(lightingRT.getTexture());
    sf::Sprite worldSprite(worldRT.getTexture());

    Card card(theDealerBackground, 
        theDealerNumbers[0], 
        theDealerSuits[0], 
        theDealerBackground, 
        sf::Color::White, 
        sf::Color::White, 
        sf::Color::White, 
        sf::Color::White);
    Chip chip(theDealerBackground);

    std::vector<IObjectAction*> clickables;

    card.setPosition({700, 400});
    chip.setPosition({500, 300});
    clickables.push_back(&card);
    clickables.push_back(&chip);

    sf::Vector2f mousePos;

    sf::Font font;
    if (!font.loadFromFile("fonts/sharetech.ttf")) {
        std::cerr << "Failed to load font\n";
    }

    sf::Text cursorText;
    cursorText.setFont(font);
    cursorText.setCharacterSize(24);
    cursorText.setFillColor(sf::Color::Blue);

    lighting.addStaticLight(Light({300, 400}, 1500.f, 0.5f, sf::Color::White));

    while (window.isOpen()) // loop when the window is open
    {
        sf::Event event; // declare an event for when an event happens
        
        while (window.pollEvent(event)) // check if window events pressed, i.e. close window
        {
            mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                for (auto* object : clickables)
                    if (object->isMouseOver(mousePos.x, mousePos.y))
                        object->onMoveStart(mousePos);
            }
            if (event.type == sf::Event::MouseMoved)
            {
                for (auto* object : clickables)
                    object->onMove(mousePos);
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                for (auto* object : clickables)
                    object->onMoveEnd(mousePos);
            }
            if (event.type == sf::Event::Closed) // check if window close pressed
            {
                window.close(); // close window
            }      
        }

        // --- UPDATE LIGHTING ----------------------------------------
        lighting.clearDynamicLights();
        lighting.addDynamicLight(Light(mousePos, 250.f, 1.0f, sf::Color::White));
        lighting.update();

        // --- RENDER LIGHTING PASS ------------------------------------
        lightingRT.clear(sf::Color::Black);
        lightingRT.draw(lighting);
        lightingRT.display();

        // --- RENDER WORLD PASS ---------------------------------------
        worldRT.clear(sf::Color::White);

        table.setScale(1.6f, 1.6f);
        sf::Vector2u texSize = table.getTexture()->getSize();
        table.setOrigin(texSize.x / 2.f, texSize.y / 2.f);
        table.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 190);

        worldRT.draw(table);
        worldRT.draw(card);
        worldRT.draw(chip);

        worldRT.display();

        // --- SHADER UNIFORMS -----------------------------------------
        ditherShader.setUniform("texture", lightingRT.getTexture());
        ditherShader.setUniform("resolution", sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

        pixelationShader.setUniform("texture", worldRT.getTexture());
        pixelationShader.setUniform("resolution", sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
        pixelationShader.setUniform("pixelSize", 4.f);

        // --- RENDER DITHER SHADER PASS -------------------------------
        ditherRT.clear(sf::Color::Transparent);
        ditherRT.draw(lightingSprite, &ditherShader);
        ditherRT.display();

        // --- FINAL COMPOSITE -----------------------------------------
        cursorText.setString(
                "X: " + std::to_string((int)mousePos.x) +
                " Y: " + std::to_string((int)mousePos.y)
            );
            cursorText.setPosition(mousePos + sf::Vector2f(10.f, -25.f)); // offset so text doesn’t overlap cursor

        window.clear();

        window.draw(worldSprite);

        sf::RenderStates lightState;
        lightState.blendMode = sf::BlendMultiply;
        window.draw(sf::Sprite(ditherRT.getTexture()), lightState);

        window.draw(cursorText);

        window.display();
    }
    
    return 0; // return 0 to finish the main function when the game is quit
}