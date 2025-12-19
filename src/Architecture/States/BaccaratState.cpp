// Custom Includes
#include "BaccaratState.hpp"
#include "../../textures.hpp"
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

BaccaratState::BaccaratState(sf::RenderWindow& w) : 
    window(w),
    lighting(SCREEN_WIDTH, SCREEN_HEIGHT),
    card(theDealerBackground,
    theDealerNumbers[0],
    theDealerSuits[0],
    theDealerBackground,
    sf::Color::White,
    sf::Color::White,
    sf::Color::White,
    sf::Color::White),
    bankStack({181.f, 625.f})
{ 
    lightingRT.create(SCREEN_WIDTH, SCREEN_HEIGHT);
    worldRT.create(SCREEN_WIDTH, SCREEN_HEIGHT);
    ditherRT.create(SCREEN_WIDTH, SCREEN_HEIGHT);

    lighting.addStaticLight(Light({300, 400}, 1500.f, 0.5f, sf::Color::White));

    card.setPosition({700, 400});
    clickables.push_back(&card);
    for (int i = 0; i < 10; ++i)
    {
        bankStack.addChip(theDealerBackground);
    }
    clickables.push_back(&bankStack);
    table.setTexture(tableTexture);

    cursorText.setFont(font);
    cursorText.setCharacterSize(24);
    cursorText.setFillColor(sf::Color::Blue);
}

void BaccaratState::handleEvent(sf::Event& event)
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
}
void BaccaratState::update(float dt)
{
    bankStack.update(dt);

    // ---UPDATE LIGHTING---
    lighting.clearDynamicLights();
    lighting.addDynamicLight(Light(mousePos, 250.f, 1.0f, sf::Color::White));
    lighting.update();

    // ---RENDER LIGHTING PASS---
    lightingRT.clear(sf::Color::Black);
    lightingRT.draw(lighting);
    lightingRT.display();

    // ---RENDER WORLD PASS---
    worldRT.clear(sf::Color::White);

    table.setScale(1.6f, 1.6f);
    sf::Vector2u texSize = table.getTexture()->getSize();
    table.setOrigin(texSize.x / 2.f, texSize.y / 2.f);
    table.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 190);

    cursorText.setString(
        "X: " + std::to_string((int)mousePos.x) +
        " Y: " + std::to_string((int)mousePos.y)
    );
    cursorText.setPosition(mousePos + sf::Vector2f(10.f, -25.f)); // offset so text doesn’t overlap cursor
}
void BaccaratState::draw(sf::RenderWindow& window)
{
    // ---SHADER UNIFORMS---
    ditherShader.setUniform("texture", lightingRT.getTexture());
    ditherShader.setUniform("resolution", sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

    pixelationShader.setUniform("texture", worldRT.getTexture());
    pixelationShader.setUniform("resolution", sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    pixelationShader.setUniform("pixelSize", 4.f);

    // ---RENDER WORLD---
    worldRT.draw(table);
    worldRT.draw(card);
    worldRT.draw(bankStack);

    worldRT.display();

    sf::Sprite worldSprite(worldRT.getTexture());
    sf::Sprite lightingSprite(lightingRT.getTexture());

    // ---RENDER DITHER---
    ditherRT.clear(sf::Color::Transparent);
    ditherRT.draw(lightingSprite, &ditherShader);
    ditherRT.display();

    // ---FINAL COMPOSITE---

    window.draw(worldSprite);

    sf::RenderStates lightState;
    lightState.blendMode = sf::BlendMultiply;
    window.draw(sf::Sprite(ditherRT.getTexture()), lightState);

    window.draw(cursorText);
}
