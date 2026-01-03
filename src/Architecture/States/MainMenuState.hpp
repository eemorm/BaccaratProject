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
#include <fstream>
#include <string>

class MainMenuState : public GameState
{
    private:
        sf::RenderWindow& window;
        GameStateManager* states;

        sf::RectangleShape background;
        sf::Text titleText;
        sf::Text copyrightText;
        UIButton playButton;
        UIButton tutorialButton;
        UIButton quitButton;

        std::string loadVersion(const std::string& path)
        {
            std::ifstream file(path);
            if (!file.is_open())
            {
                std::cerr << "Failed to open version file: " << path << "\n";
                return "Unknown";
            }

            std::string version;
            std::getline(file, version); // read the first line
            return version;
        }
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
                    states->changeState(StateID::Baccarat, window, false);
                }
            ),
            tutorialButton(
                sf::Vector2f(SCREEN_WIDTH/2 - 100, 475),
                sf::Vector2f(200, 50),
                "Tutorial",
                font,
                [&]() {
                    states->changeState(StateID::Baccarat, window, true);
                }
            ),
            quitButton(
                sf::Vector2f(SCREEN_WIDTH/2 - 100, 550),
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
            titleText.setString("CROUPIER DEMO");
            titleText.setCharacterSize(72);
            titleText.setFillColor(sf::Color::White);
 
            sf::FloatRect bounds = titleText.getLocalBounds();
            titleText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
            titleText.setPosition(SCREEN_WIDTH / 2.f, 200.f);

            copyrightText.setFont(font);
            std::string version = loadVersion("version.txt");
            copyrightText.setString("Copyright 2026 by Memento Studios - Version " + version);
            copyrightText.setCharacterSize(24);
            copyrightText.setFillColor(sf::Color::White);

            bounds = copyrightText.getLocalBounds();
            copyrightText.setOrigin(bounds.width, bounds.height);
            copyrightText.setPosition(1325, 735.f);

            stopAllMusic();
            m_maintheme->play();
        }

        inline void handleEvent(sf::Event& event) override
        {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            playButton.handleEvent(event, mousePos);
            tutorialButton.handleEvent(event, mousePos);
            quitButton.handleEvent(event, mousePos);
        }
        inline void update(float dt) override
        {
            playButton.update(dt);
            tutorialButton.update(dt);
            quitButton.update(dt);
        }
        inline void draw(sf::RenderWindow& window) override
        {
            window.draw(background);
            window.draw(titleText);
            window.draw(copyrightText);
            window.draw(playButton);
            window.draw(tutorialButton);
            window.draw(quitButton);
        }
};