#pragma once

// Custom Includes
#include "../../textures.hpp"
#include "../../audio.hpp"
#include "../GameState.hpp"
#include "../GameStateManager.hpp"
#include "../../UI/Elements/UIButton.hpp"

// SFML
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// Standard Libraries
#include <iostream>
#include <vector>

class DeathState : public GameState
{
    private:
        sf::RenderWindow& window;
        GameStateManager* states;

        sf::RectangleShape background;
        sf::Text deathText;
        UIButton tryAgainButton;
        UIButton mainMenuButton;
    public:
        inline DeathState(sf::RenderWindow& w, GameStateManager* gsm) : 
            window(w), 
            states(gsm),
            tryAgainButton(
                sf::Vector2f(SCREEN_WIDTH/2 - 100, 400),
                sf::Vector2f(200, 50),
                "Try Again",
                font,
                [&]() {
                    states->changeState(StateID::Baccarat, window, false);
                }
            ),
            mainMenuButton(
                sf::Vector2f(SCREEN_WIDTH/2 - 100, 500),
                sf::Vector2f(200, 50),
                "Main Menu",
                font,
                [&]() {
                    states->changeState(StateID::MainMenu, window);
                }
            )
        { 
            background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
            background.setFillColor(sf::Color(20, 20, 30));

            deathText.setFont(font);
            deathText.setString("YOU LOST");
            deathText.setCharacterSize(72);
            deathText.setFillColor(sf::Color::White);

            sf::FloatRect bounds = deathText.getLocalBounds();
            deathText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
            deathText.setPosition(SCREEN_WIDTH / 2.f, 200.f);

            stopAllMusic();
            m_falling->play();
        }

        inline void handleEvent(sf::Event& event) override
        {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            tryAgainButton.handleEvent(event, mousePos);
            mainMenuButton.handleEvent(event, mousePos);
        }
        inline void update(float dt) override
        {
            tryAgainButton.update(dt);
            mainMenuButton.update(dt);
        }
        inline void draw(sf::RenderWindow& window) override
        {
            window.draw(background);
            window.draw(deathText);
            window.draw(tryAgainButton);
            window.draw(mainMenuButton);
        }
};