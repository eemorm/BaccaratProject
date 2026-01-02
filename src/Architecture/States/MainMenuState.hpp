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

class MainMenuState : public GameState
{
    private:
        sf::RenderWindow& window;
        GameStateManager* states;

        sf::RectangleShape background;
        sf::Text titleText;
        sf::Text copyrightText;
        UIButton playButton;
        UIButton quitButton;
    public:
        inline MainMenuState(sf::RenderWindow& w, GameStateManager* gsm) : 
            window(w), 
            states(gsm),
            playButton(
                sf::Vector2f(SCREEN_WIDTH/2 - 100, 400),
                sf::Vector2f(200, 50),
                "Play",
                font,
                [&]() {
                    states->changeState(StateID::Baccarat, window);
                }
            ),
            quitButton(
                sf::Vector2f(SCREEN_WIDTH/2 - 100, 500),
                sf::Vector2f(200, 50),
                "Quit",
                font,
                [&]() {
                    window.close();
                }
            )
        { 
            background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
            background.setFillColor(sf::Color(20, 20, 30));

            titleText.setFont(font);
            titleText.setString("BACCARAT PROJECT");
            titleText.setCharacterSize(72);
            titleText.setFillColor(sf::Color::White);

            sf::FloatRect bounds = titleText.getLocalBounds();
            titleText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
            titleText.setPosition(SCREEN_WIDTH / 2.f, 200.f);

            copyrightText.setFont(font);
            copyrightText.setString("Copyright 2026 by Memento Studios");
            copyrightText.setCharacterSize(24);
            copyrightText.setFillColor(sf::Color::White);

            bounds = copyrightText.getLocalBounds();
            copyrightText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
            copyrightText.setPosition(1165, 725.f);

            stopAllMusic();
            m_maintheme->play();
        }

        inline void handleEvent(sf::Event& event) override
        {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            playButton.handleEvent(event, mousePos);
            quitButton.handleEvent(event, mousePos);
        }
        inline void update(float dt) override
        {
            playButton.update(dt);
            quitButton.update(dt);
        }
        inline void draw(sf::RenderWindow& window) override
        {
            window.draw(background);
            window.draw(titleText);
            window.draw(copyrightText);
            window.draw(playButton);
            window.draw(quitButton);
        }
};