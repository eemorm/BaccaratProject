#pragma once

// Custom Includes
#include "BaccaratState.hpp"
#include "../../textures.hpp"
#include "../GameState.hpp"
#include "../../Classes/Card.hpp"
#include "../../Classes/Deck.hpp"
#include "../../Classes/ChipStack.hpp"
#include "../../Classes/Interfaces/IObjectAction.hpp"
#include "../../Classes/Baccarat/BaccaratGame.hpp"
#include "../../Classes/Baccarat/BaccaratBet.hpp"
#include "../../Classes/LightSystem.hpp"
#include "../../audio.hpp"

// SFML
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// Standard Libraries
#include <iostream>
#include <vector>

/*
    class BaccaratState 

    Runs from the GameStateManager, which is run from main.cpp.
    Manages all aspects of the baccarat game, including rendering, updating, and event handling.
    Used to separate game logic from main application flow for better organization.
    Runs during the baccarat game only, and is switched by the GameStateManager.
*/
class BaccaratState : public GameState
{
    private:
        //---WINDOW---
        sf::RenderWindow& window; // window; comes from Game class which comes from main.cpp; passed by reference for rendering

        //---LIGHTING---
        LightSystem lighting; // light system to manage the lighting
        sf::RenderTexture lightingRT; // render texture for lighting pass
        sf::RenderTexture worldRT; // render texture for world pass
        sf::RenderTexture ditherRT; // render texture for the dither shader

        //---GAME OBJECTS---
        // NOTE: order of these declarations matters for initialization order
        Deck deck; // deck object, which is literally a virtual representation of a deck of cards. its just that simple
        BaccaratGame game; // baccarat game object, which manages and ties the game logic of baccarat together
        ChipStack bankStack; // chip stack for betting
        sf::Sprite table; // table sprite
        //-------------------
        std::vector<IObjectAction*> clickables; // declare clickables array to store references to clickable objects

        //---BETTING---
        sf::FloatRect bankerBetZone; // betting zone for banker
        sf::FloatRect tieBetZone; // betting zone for tie
        sf::FloatRect playerBetZone; // betting zone for player
        int chipWealth = 0;
    
        //---MISC---
        sf::Vector2f mousePos; // mouse position
        bool roundOver = false;
        sf::Text cursorText; // text to display cursor position for debugging; always updates
        sf::Text moneyText;
        sf::Text phaseText;
        sf::Text winText;
        sf::Text payoutText;
    public:
        // constructor, initializes objects that don't have default constructors
        inline BaccaratState(sf::RenderWindow& w) : 
            window(w),
            lighting(SCREEN_WIDTH, SCREEN_HEIGHT),
            deck(theDealerBackground, theDealerBackground, theDealerNumbers, theDealerSuits, theDealerBackground),
            game(deck),
            bankStack({181.f, 625.f})
        { 
            //---CREATE RENDER TEXTURES---
            lightingRT.create(SCREEN_WIDTH, SCREEN_HEIGHT);
            worldRT.create(SCREEN_WIDTH, SCREEN_HEIGHT);
            ditherRT.create(SCREEN_WIDTH, SCREEN_HEIGHT);

            //---STATIC LIGHTS---
            lighting.addStaticLight(Light({300, 400}, 1500.f, 0.5f, sf::Color::White));

            //---PREPARE GAME OBJECTS---
            deck.setPosition({1100, 600});
            deck.shuffleDeck();
            for (int i = 0; i < 10; ++i)
            {
                bankStack.addChip(theDealerBackground);
            }
            clickables.push_back(&bankStack);
            //---SET UP TABLE---
            table.setTexture(tableTexture);
            table.setScale(1.6f, 1.6f);
            sf::Vector2u texSize = table.getTexture()->getSize();
            table.setOrigin(texSize.x / 2.f, texSize.y / 2.f);
            table.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 190);

            //---INITIALIZE BET ZONES---
            bankerBetZone = { 499, 532, 602, 617 };
            tieBetZone = { 617, 563, 776, 617 };
            playerBetZone = { 762, 564, 915, 589 };

            //---SET UP CURSOR TEXT---
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

            game.startRound(); // start the round of baccarat
            playRandom(baccarat1);
        }

        // handles events such as mouse movement and clicks, passed from GameStateManager which is run from main.cpp
        inline void handleEvent(sf::Event& event) override
        {
            mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window)); // get mouse position in world coordinates

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) // left mouse button down
            {
                for (auto* object : clickables) // for object (pointer to item with IObjectAction) in clickables
                    if (object->isMouseOver(mousePos.x, mousePos.y))
                        object->onMoveStart(mousePos); // start moving object
            }
            if (event.type == sf::Event::MouseMoved) // if mouse moved
            {
                for (auto* object : clickables)
                    object->onMove(mousePos); // update object position based on mouse movement
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) // on left mouse button release
            {
                if (!game.isBettingOpen()) // initial check for if betting is closed
                {
                    for (auto* object : clickables)
                        object->onMoveEnd(mousePos); // end the movement of all clickables
                    return;
                }

                int chipsInHand = bankStack.getHeldChips().size(); // get number of chips in hand
                if (chipsInHand == 0) return; // failsafe check for if no chips are being held
    
                BetTarget target = BetTarget::None; // initialize bet target to check for bet zone and mouse interaction with bets
    
                // check which bet zone the mouse is in
                if (playerBetZone.contains(mousePos))
                    target = BetTarget::Player;
                else if (bankerBetZone.contains(mousePos))
                    target = BetTarget::Banker;
                else if (tieBetZone.contains(mousePos))
                    target = BetTarget::Tie;
    
                // if a bet target was selected, place the bet with the correct amount and close betting phase
                if (target != BetTarget::None)
                {
                    int amount = chipsInHand * bankStack.getChipValue(); // calculate bet amount based on number of chips and chip value
                    game.placeBet(target, amount); // place the bet

                    bankStack.acceptBet(); // transfer chips by having bank stack accept the bet
                    game.closeBetting(); // finish the betting phase with a call to BaccaratGame
                }

                // final failsafe for if betting phase is going on, but no bet target was selected
                for (auto* object : clickables)
                    object->onMoveEnd(mousePos);
            }   
        }
        // updates every frame with respect to delta time
        inline void update(float dt) override
        {
            bankStack.update(dt); // update the bank stack for lerping chips back if they are released with respect to the rules in handleEvent and delta time
            game.update(dt); // update the baccarat game logic with respect to delta time

            //---UPDATE LIGHTING---
            //lighting.clearDynamicLights(); // clear moving lights from last frame to update
            //lighting.addDynamicLight(Light(mousePos, 250.f, 1.0f, sf::Color::White)); // add back dynamic lights in order to give the appearance of movement
            lighting.update(); // draw lighting (but not to RT yet)

            //---RENDER LIGHTING PASS---
            lightingRT.clear(sf::Color::Black); // clear lighting RT to black so that holes can be cut to show lighting
            lightingRT.draw(lighting); // draw lighting on RT
            lightingRT.display(); // display lightingRT (but not drawn to window yet)

            //---RENDER WORLD PASS---
            worldRT.clear(sf::Color::White); // clear worldRT to have white as a background

            if (!roundOver)
            {
                if (game.isRoundFinished())
                {
                    roundOver = true;
                    int winnings = game.payout();
                    chipWealth += winnings;
                    payoutText.setString("Payout: $" + std::to_string(winnings));
                }
            }

            //---UPDATE CURSOR TEXT---
            cursorText.setString(
                "X: " + std::to_string((int)mousePos.x) +
                " Y: " + std::to_string((int)mousePos.y)
            );
            cursorText.setPosition(mousePos + sf::Vector2f(10.f, -25.f)); // offset so text doesn’t overlap cursor

            moneyText.setString(
            "Bet: $" + std::to_string(game.getBetAmount()) + 
            "\nWealth: $" + std::to_string(chipWealth)
            );

            phaseText.setString(game.phaseToString(game.getPhase()));

            winText.setString(game.resultToString());
        }
        // draws everything to the screen
        inline void draw(sf::RenderWindow& window) override
        {
            //---SHADER UNIFORMS---
            // shader uniforms set; basically just settings to set the shader with the render texture and screen resolution
            ditherShader.setUniform("texture", lightingRT.getTexture());
            ditherShader.setUniform("resolution", sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

            pixelationShader.setUniform("texture", worldRT.getTexture());
            pixelationShader.setUniform("resolution", sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
            pixelationShader.setUniform("pixelSize", 4.f);

            //---RENDER WORLD---
            worldRT.draw(table); // draw table at first z-layer
            worldRT.draw(deck); // draw deck on top of table

            // then draw player and banker hands
            sf::Vector2f startPos = { 595, 692 }; // starting position for player hand
            float spacing = 100.f; // spacing between cards

            for (int i = 0; i < game.getPlayerHand().getCards().size(); i++) 
            {
                Card& c = game.getPlayerHand().getCards()[i]; // get each card in hand
                c.setPosition(startPos + sf::Vector2f(i * spacing, 0)); // set position relative to starting position and spacing
                worldRT.draw(c); // draw card to render texture
            }

            startPos = { 595, 470 }; // starting position for banker hand
            for (int i = 0; i < game.getBankerHand().getCards().size(); i++) // basically same loop as player hand but for banker
            {
                Card& c = game.getBankerHand().getCards()[i];
                c.setPosition(startPos + sf::Vector2f(i * spacing, 0));
                worldRT.draw(c);
            }

            worldRT.draw(bankStack); // draw bank stack on top of everything else to ensure visibility over other stuff when dragging

            worldRT.display(); // display worldRT (but not drawn to window yet)

            // set render textures to sprites for final composite onto the screen to draw frame
            sf::Sprite worldSprite(worldRT.getTexture());
            sf::Sprite lightingSprite(lightingRT.getTexture());

            //---RENDER DITHER---
            ditherRT.clear(sf::Color::Transparent); // clear ditherRT
            ditherRT.draw(lightingSprite, &ditherShader); // draw lighting sprite with dither shader applied
            ditherRT.display(); // display ditherRT (but not drawn to window yet)

            //---FINAL COMPOSITE---
            window.draw(worldSprite); // draw world sprite to window first

            sf::RenderStates lightState;
            lightState.blendMode = sf::BlendMultiply; // blend lighting for dithered lighting effect
            window.draw(sf::Sprite(ditherRT.getTexture()), lightState); // draw dithered lighting on top of world

            //---DRAW CURSOR TEXT---
            window.draw(cursorText);
            window.draw(moneyText);
            window.draw(phaseText);
            window.draw(winText);
            window.draw(payoutText);
        }
};