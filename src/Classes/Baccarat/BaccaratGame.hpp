#pragma once

// Custom Includes
#include "BaccaratHand.hpp"
#include "BaccaratResult.hpp"
#include "BaccaratRules.hpp"
#include "../Deck.hpp"

// Standard Libraries
#include <vector>
#include <random>
#include <optional>

class BaccaratGame
{
    private:
        enum class BaccaratPhase
        {
            Idle,
            Betting,
            DealingInitial,
            PlayerThirdCard,
            BankerThirdCard,
            Resolve,
            Finished
        };

        BaccaratHand playerHand;
        BaccaratHand bankerHand;
        std::mt19937 rng;
        BaccaratPhase phase = BaccaratPhase::Idle;
        float phaseTimer = 0.f;
        Deck& deck;
    public:
        BaccaratGame(Deck& d) : deck(d) { rng = std::mt19937{ std::random_device{}() };}
        Card drawCard() { return deck.drawCardFromDeck(); }
        void startRound() 
        {
            playerHand.clear();
            bankerHand.clear();
            phase = BaccaratPhase::DealingInitial;
            phaseTimer = 0.f;
        }
        void dealInitial()
        {
            if (phaseTimer < 0.5f) return;

            phaseTimer = 0.f;

            if (playerHand.getCards().size() < 2)
                playerHand.addCard(drawCard());
            else if (bankerHand.getCards().size() < 2)
                bankerHand.addCard(drawCard());
            else
                phase = BaccaratPhase::PlayerThirdCard;
        }
        void playerThirdCard()
        {
            if (!doesPlayerDrawAThirdCard(playerHand))
            {
                phase = BaccaratPhase::BankerThirdCard;
                return;
            }

            if (phaseTimer >= 0.5f)
            {
                playerHand.addCard(drawCard());
                phase = BaccaratPhase::BankerThirdCard;
                phaseTimer = 0.f;
            }
        }
        void bankerThirdCard()
        {
            if (!doesBankerDrawAThirdCard(bankerHand, *playerHand.getThirdCard()))
            {
                phase = BaccaratPhase::Resolve;
                return;
            }

            if (phaseTimer >= 0.5f)
            {
                bankerHand.addCard(drawCard());
                phase = BaccaratPhase::Resolve;
            }
        }
        BaccaratResult resultOfGame() { return determineWinner(playerHand, bankerHand);}
        BaccaratHand& getPlayerHand() { return playerHand; }
        BaccaratHand& getBankerHand() { return bankerHand; }
        void update(float dt)
        {
            phaseTimer += dt;

            switch (phase)
            {
                case BaccaratPhase::DealingInitial:
                    dealInitial();
                    break;

                case BaccaratPhase::PlayerThirdCard:
                    playerThirdCard();
                    break;

                case BaccaratPhase::BankerThirdCard:
                    bankerThirdCard();
                    break;

                case BaccaratPhase::Resolve:
                    phase = BaccaratPhase::Finished;
                    break;

                default:
                    break;
            }
        }
};