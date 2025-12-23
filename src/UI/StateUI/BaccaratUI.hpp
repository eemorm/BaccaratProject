#pragma once

// Custom Includes
#include "../../textures.hpp"
#include "../UIManager.hpp"
#include "../Elements/UIButton.hpp"
#include "../../Classes/Baccarat/BaccaratGame.hpp"

class BaccaratUI : public sf::Drawable
{
    private:
        UIManager ui;
        BaccaratGame& game;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        { 
            for (auto& element : ui.getElements())
                target.draw(*element, states);
            target.draw(cursorText, states);
            target.draw(moneyText, states);
            target.draw(phaseText, states);
            target.draw(winText, states);
            target.draw(payoutText, states);
        }
    public:
        sf::Text cursorText;
        sf::Text moneyText;
        sf::Text phaseText;
        sf::Text winText;
        sf::Text payoutText;
        UIButton& confirmBetButton;
    
        BaccaratUI(BaccaratGame& g) : game(g), confirmBetButton(ui.add<UIButton>
            (
                sf::Vector2f(1146, 75),
                sf::Vector2f(200, 50),
                "Confirm Bet",
                font,
                [&]() {
                    if (game.isBettingOpen() && game.getBetAmount() > 0)
                    {
                        game.closeBetting();
                        confirmBetButton.setActive(false);
                    }
                }
            ))
        {
            cursorText.setFont(font);
            cursorText.setCharacterSize(24);
            cursorText.setFillColor(sf::Color::Blue);

            moneyText.setFont(font);
            moneyText.setCharacterSize(24);
            moneyText.setFillColor(sf::Color::White);
            moneyText.setPosition(20.f, 20.f);

            phaseText.setFont(font);
            phaseText.setCharacterSize(24);
            phaseText.setFillColor(sf::Color::White);
            phaseText.setPosition(1175.f, 20.f);

            winText.setFont(font);
            winText.setCharacterSize(96);
            winText.setPosition(20.f, 100.f);
            winText.setFillColor(sf::Color(255, 255, 255, 255));
            winText.setStyle(sf::Text::Bold);

            payoutText.setFont(font);
            payoutText.setCharacterSize(96);
            payoutText.setPosition(20.f, 200.f);
            payoutText.setFillColor(sf::Color(255, 255, 255, 255));
            payoutText.setStyle(sf::Text::Bold);
        }
        void handleEvent(sf::Event& event, sf::Vector2f mouse) { ui.handleEvent(event, mouse); }
        void update(float dt) { ui.update(dt); }
};