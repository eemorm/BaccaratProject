#pragma once

// Custom Includes
#include "../../textures.hpp"
#include "../GameState.hpp"
#include "../GameStateManager.hpp"
#include "../../Classes/Card.hpp"
#include "../../Classes/Deck.hpp"
#include "../../Classes/ChipStack.hpp"
#include "../../Classes/WealthManager.hpp"
#include "../../Classes/Interfaces/IObjectAction.hpp"
#include "../../Baccarat/BaccaratGame.hpp"
#include "../../Classes/ItemDatabase.hpp"
#include "../../Classes/Shop.hpp"
#include "../../Classes/Inventory.hpp"
#include "../../Classes/Complex.hpp"
#include "../../Classes/PlayerCombat.hpp"
#include "../../Classes/PlayerHealth.hpp"
#include "../../Classes/PlayerStats.hpp"
#include "../../Classes/CombatSystem.hpp"
#include "../../Classes/EdgeManager.hpp"
#include "../../Classes/TutorialController.hpp"
#include "../../Classes/LightSystem.hpp"
#include "../../UI/StateUI/BaccaratUI.hpp"
#include "../../UI/Elements/SpeechBox.hpp"
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
        enum class RoundState
        {
            Baccarat,
            ChoosingEdge,
            NextFloor
        };

        //---WINDOW---
        sf::RenderWindow& window; // window; comes from Game class which comes from main.cpp; passed by reference for rendering
        GameStateManager* states;

        //---LIGHTING---
        LightSystem lighting; // light system to manage the lighting
        sf::RenderTexture lightingRT; // render texture for lighting pass
        sf::RenderTexture worldRT; // render texture for world pass
        sf::RenderTexture ditherRT; // render texture for the dither shader

        //---PLAYER STATS--- (yes it gets its own category)
        PlayerStats playerStats;

        //---GAME OBJECTS---
        // NOTE: order of these declarations matters for initialization order
        Deck deck; // deck object, which is literally a virtual representation of a deck of cards. its just that simple
        BaccaratGame game; // baccarat game object, which manages and ties the game logic of baccarat together
        ChipStack* chosenStack = nullptr;
        sf::Sprite table; // table sprite
        sf::Sprite background;
        //-------------------
        std::vector<IObjectAction*> clickables; // declare clickables array to store references to clickable objects

        //---BETTING AND WEALTH---
        WealthManager chipWealthManager; // wealth manager to manage player's wealth
        sf::FloatRect originalBankerBetZone;
        sf::FloatRect originalTieBetZone;
        sf::FloatRect originalPlayerBetZone;
        sf::FloatRect bankerBetZone; // betting zone for banker
        sf::FloatRect tieBetZone; // betting zone for tie
        sf::FloatRect playerBetZone; // betting zone for player
        bool roundOver = false; // flag to check if round is over, used to trigger payout only once
    
        //---SHOP AND PLAYER---
        PlayerHealth playerHealth;
        Inventory inventory;
        Shop shop;
        PlayerCombat playerCombat;

        //---COMPLEX AND FLOW---
        Complex complex;
        RoundState roundState = RoundState::Baccarat;

        //---COMBAT SYSTEM---
        CombatSystem combatSystem;

        //---EDGES---
        EdgeManager edgeManager;

        //---UI---
        BaccaratUI ui;
        sf::Clock floorTransitionClock;

        //---TUTORIAL---
        bool showTutorial;
        TutorialController tutorial;
        SpeechBox dealerSpeech;

        //---MISC---
        sf::Vector2f mousePos; // mouse position
    public:
        // constructor, initializes objects that don't have default constructors
        inline BaccaratState(sf::RenderWindow& w, GameStateManager* gsm, bool st) : 
            window(w),
            states(gsm),
            lighting(SCREEN_WIDTH, SCREEN_HEIGHT),
            deck(theDealerBackground, theDealerBackground, theDealerNumbers, theDealerSuits, theDealerBackground),
            game(deck, playerStats),
            playerHealth(100.f, playerStats),
            inventory(&playerHealth),
            shop(&inventory, &chipWealthManager, playerStats),
            playerCombat(&inventory),
            combatSystem(&complex, &playerCombat, &playerHealth),
            showTutorial(st)
        { 
            //---CREATE RENDER TEXTURES---
            lightingRT.create(SCREEN_WIDTH, SCREEN_HEIGHT);
            worldRT.create(SCREEN_WIDTH, SCREEN_HEIGHT);
            ditherRT.create(SCREEN_WIDTH, SCREEN_HEIGHT);

            //---STATIC LIGHTS---
            lighting.addStaticLight(Light({300, 400}, 1500.f, 0.7f, sf::Color::White, true));

            //---SET UP WEALTH MANAGER---
            chipWealthManager.initializeManager();
            chipWealthManager.setWealth(385);

            //---PREPARE GAME OBJECTS---
            deck.setPosition({1100, 600});
            deck.shuffleDeck();

            for (auto* stack : chipWealthManager.getStacks())
                clickables.push_back(stack);

            //---SET UP TABLE---
            table.setTexture(tableTexture);
            table.setScale(1.6f, 1.6f);
            sf::Vector2u texSize = table.getTexture()->getSize();
            table.setOrigin(texSize.x / 2.f, texSize.y / 2.f);
            table.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 190);

            background.setTexture(backgroundTexture);
            background.setScale(2.67f, 2.67f);
            background.setPosition(0, 0);
            background.setColor(sf::Color(180, 180, 180, 255));

            theDealer.setScale(0.3f, 0.3f);
            sf::Vector2u texSize2 = theDealer.getTexture()->getSize();
            theDealer.setOrigin(texSize2.x / 2.f, texSize2.y / 2.f);
            theDealer.setPosition(SCREEN_WIDTH / 2 - 40, SCREEN_HEIGHT / 2 - 125);

            //---INITIALIZE BET ZONES---
            bankerBetZone = { 499.f, 532.f, 103.f, 85.f };
            tieBetZone = { 617.f, 563.f, 159.f, 54.f };
            playerBetZone = { 762.f, 564.f, 153.f, 25.f };
            originalBankerBetZone = bankerBetZone;
            originalTieBetZone = tieBetZone;
            originalPlayerBetZone = playerBetZone;

            //---SHOP---
            shop.initializeShop(complex.getFloor());

            //---COMPLEX AND FLOW---
            complex.spawnEnemiesForFloor();

            //---UI---
            ui.confirmBetButton.setOnClick([this]() { if (game.getGamePhase() == BaccaratPhase::Betting && game.getBetAmount() > 0) { game.closeBetting(); ui.confirmBetButton.setActive(false); }});
            ui.restartGameButton.setOnClick([this]() { restartGame(); ui.restartGameButton.setActive(false); });
            ui.restartGameButton.setActive(false);

            if (showTutorial) 
            {
                tutorial.start();
                dealerSpeech.setText(tutorial.getText());
                dealerSpeech.setAnchor(theDealer.getPosition() + sf::Vector2f(160, -120));
            }

            game.startRound(); // start the round of baccarat
            stopAllMusic();
            playRandom(baccarat1);
        }

        // handles events such as mouse movement and clicks, passed from GameStateManager which is run from main.cpp
        inline void handleEvent(sf::Event& event) override
        {
            mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window)); // get mouse position in world coordinates

            if (roundState == RoundState::ChoosingEdge)
            {
                if (edgeManager.handleEvent(event, mousePos))
                {
                    Edge& chosen = edgeManager.getSelectedEdge();
                    playerStats.applyEdge(chosen);

                    edgeManager.close();

                    roundState = RoundState::NextFloor;
                    floorTransitionClock.restart();

                    complex.nextFloor();
                    shop.initializeShop(complex.getFloor());
                    chipWealthManager.addWealth(200 + playerStats.getFloorMoneyReturnBonus());
                }

                return;
            }
            if (roundState == RoundState::NextFloor)
                return; 

            shop.handleEvent(event, mousePos);
            if (shop.getShopOpen()) return;

            ui.handleEvent(event, mousePos);

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) // left mouse button down
            {
                for (auto* object : clickables) // for object (pointer to item with IObjectAction) in clickables
                    if (object->isMouseOver(mousePos.x, mousePos.y))
                    {
                        object->onMoveStart(mousePos); // start moving object
                        chosenStack = dynamic_cast<ChipStack*>(object);
                    }

                combatSystem.handlePlayerClick(mousePos);
            }
            if (event.type == sf::Event::MouseMoved) // if mouse moved
            {
                for (auto* object : clickables)
                    object->onMove(mousePos); // update object position based on mouse movement
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) // on left mouse button release
            {
                if (game.getGamePhase() != BaccaratPhase::Betting) // initial check for if betting is closed
                {
                    for (auto* object : clickables)
                        object->onMoveEnd(mousePos); // end the movement of all clickables
                    return;
                }

                if (!chosenStack) return;
            
                int chipsInHand = chosenStack->getHeldChips().size(); // get number of chips in hand
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
                    int amount = chipsInHand * chosenStack->getChipValue(); // calculate bet amount based on number of chips and chip value
                    game.placeBet(target, amount); // place the bet
                    chosenStack->acceptBet(); // transfer chips by having bank stack accept the bet
                    chipWealthManager.addWealth(-amount); // deduct bet amount from player's wealth
                    
                    game.lockBetZones(target, bankerBetZone, tieBetZone, playerBetZone); // lock bet zones based on first bet placed
                }

                // final failsafe for if betting phase is going on, but no bet target was selected
                for (auto* object : clickables)
                    object->onMoveEnd(mousePos);

                chosenStack = nullptr;
            }   
        }
        // updates every frame with respect to delta time
        inline void update(float dt) override
        {
            static std::string lastText;
            tutorial.update(dt);

            if (showTutorial && tutorial.isActive())
            {
                std::string currentText = tutorial.getText();
                if (currentText != lastText) 
                {
                    dealerSpeech.setText(currentText);
                    dealerSpeech.setAnchor(theDealer.getPosition() + sf::Vector2f(160, -120));
                    lastText = currentText;
                }
                dealerSpeech.update(dt);
            }

            if (showTutorial && !tutorial.isActive())
            {
                states->changeState(StateID::MainMenu, window);
                return;
            }

            if (roundState == RoundState::NextFloor)
            {
                sf::FloatRect bounds = ui.floorText.getLocalBounds();
                ui.floorText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
                ui.floorText.setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
                ui.floorText.setString("FLOOR " + std::to_string(complex.getFloor()));
                if (floorTransitionClock.getElapsedTime().asSeconds() >= 1.2f)
                {
                    restartGame();
                    roundState = RoundState::Baccarat;
                }
                return;
            }

            for (auto* object : chipWealthManager.getStacks())
                object->update(dt); // update wealth manager to update chip stacks
            game.update(dt); // update the baccarat game logic with respect to delta time

            //---UPDATE LIGHTING---
            //lighting.clearDynamicLights(); // clear moving lights from last frame to update
            //lighting.addDynamicLight(Light(mousePos, 250.f, 1.0f, sf::Color::White)); // add back dynamic lights in order to give the appearance of movement
            lighting.update(dt); // draw lighting (but not to RT yet)

            //---RENDER LIGHTING PASS---
            lightingRT.clear(sf::Color::Black); // clear lighting RT to black so that holes can be cut to show lighting
            lightingRT.draw(lighting); // draw lighting on RT
            lightingRT.display(); // display lightingRT (but not drawn to window yet)

            //---RENDER WORLD PASS---
            worldRT.clear(sf::Color::White); // clear worldRT to have white as a background

            //---CHECK FOR ROUND OVER AND PAYOUT---
            if (!roundOver)
            {
                if (game.getGamePhase() == BaccaratPhase::Finished)
                {
                    roundOver = true;
                    int winnings = game.payout();
                    chipWealthManager.addWealth(winnings);
                    ui.payoutText.setString("Payout: $" + std::to_string(winnings));
                    if (chipWealthManager.getWealth() > 0)
                        ui.restartGameButton.setActive(true);
                    else if (chipWealthManager.getWealth() == 0 && !showTutorial)
                    {
                        states->changeState(StateID::Death, window);
                        return;
                    }
                    else if (showTutorial)
                    {
                        chipWealthManager.addWealth(2000);
                        ui.payoutText.setString("You tried to lose.");
                        ui.restartGameButton.setActive(true);
                    }
                }
            }

            if (roundState == RoundState::Baccarat && complex.getCurrentEnemies().empty())
            {
                roundState = RoundState::ChoosingEdge;

                edgeManager.initializeEdges();
                edgeManager.open();
            }

            combatSystem.update();

            if (playerHealth.getCurrentHealth() <= 0 && !showTutorial)
            {
                states->changeState(StateID::Death, window);
                return;
            }

            //---UPDATE TEXT---
            bool hoveringEnemy = false;
            bool hoveringChip = false;
            int chipHoverValue = 0;
            sf::Vector2f enemyPos;
            int enemyCurrentHealth;
            int enemyMaxHealth;

            for (auto& enemy : complex.getCurrentEnemies())
            {
                if (enemy->getSprite().getGlobalBounds().contains(mousePos))
                {
                    hoveringEnemy = true;
                    ui.enemyName.setString(enemy->getData()->name);
                    enemyPos = enemy->getSprite().getPosition();
                    enemyCurrentHealth = enemy->getCurrentHealth();
                    enemyMaxHealth = enemy->getMaxHealth();
                    break;
                }
            }

            for (auto& stack : chipWealthManager.getStacks())
            {
                if (stack->isMouseInBounds(mousePos))
                {
                    hoveringChip = true;
                    chipHoverValue = stack->getChipValue();
                    break;
                }
            }

            if (hoveringEnemy)
            {
                ui.showEnemyStats = true;
                if (inventory.getAttacks() > 0)
                    ui.cursorText.setString("ATTACK");
                else
                    ui.cursorText.setString("NEED ATTACKS");
            }
            else if (hoveringChip)
                ui.cursorText.setString("$" + std::to_string(chipHoverValue));
            else
                ui.cursorText.setString("");

            ui.cursorText.setPosition(mousePos + sf::Vector2f(10.f, -25.f)); // offset so text doesn’t overlap cursor
            ui.moneyText.setString("Bet: $" + std::to_string(game.getBetAmount()) + "\nWealth: $" + std::to_string(chipWealthManager.getWealth()));
            ui.attacksText.setString("Attacks: " + std::to_string(inventory.getAttacks()));
            ui.winText.setString(game.resultToString());
            ui.healthText.setString(std::to_string(playerHealth.getCurrentHealth()) + "/" + std::to_string(playerHealth.getMaxHealth()));
            ui.healthBar.updateBar(playerHealth.getCurrentHealth());

            ui.enemyName.setPosition(enemyPos + sf::Vector2f(10.f, -55.f));
            ui.enemyHealthBar.setPosition(enemyPos + sf::Vector2f(10.f, -25.f));
            ui.enemyHealthBar.updateBarWithMax(enemyCurrentHealth, enemyMaxHealth);
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
            worldRT.draw(background);
            worldRT.draw(theDealer);
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

            for (auto& enemy : complex.getCurrentEnemies())
            {
                worldRT.draw(*enemy);
            }

            worldRT.draw(chipWealthManager); // draw all chip stacks managed by wealth manager on top of everything else to ensure visibility over other stuff when dragging

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

            if (!shop.getShopOpen())
                window.draw(ui); // draw UI on top of everything else
            if (ui.showEnemyStats && !shop.getShopOpen())
            {
                window.draw(ui.enemyHealthBar);
                window.draw(ui.enemyName);
            }
            if (showTutorial && tutorial.isActive())
            {
                window.draw(dealerSpeech);
            }
            window.draw(shop);
            window.draw(edgeManager);
            if (roundState == RoundState::NextFloor)
            {
                sf::RectangleShape dim({ SCREEN_WIDTH, SCREEN_HEIGHT });
                dim.setFillColor(sf::Color(0, 0, 0, 200));
                window.draw(dim);

                window.draw(ui.floorText);
            }
        }

        void restartGame()
        {
            roundOver = false;

            bankerBetZone = originalBankerBetZone;
            tieBetZone = originalTieBetZone;
            playerBetZone = originalPlayerBetZone;

            ui.winText.setString("");
            ui.payoutText.setString("");
            ui.confirmBetButton.setActive(true);
            ui.restartGameButton.setActive(false);

            game.startRound();
        }
};