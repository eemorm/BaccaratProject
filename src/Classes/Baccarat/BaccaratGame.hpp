#pragma once

// Custom Includes
#include "BaccaratHand.hpp"
#include "BaccaratResult.hpp"
#include "BaccaratRules.hpp"
#include "BaccaratBet.hpp"
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
        struct Bet
        {
            BetTarget target = BetTarget::None;
            int amount = 0;
        };

        BaccaratHand playerHand;
        BaccaratHand bankerHand;
        std::mt19937 rng;
        BaccaratPhase phase = BaccaratPhase::Idle;
        float phaseTimer = 0.f;
        Deck& deck;
        Bet currentBet;
    public:
        BaccaratGame(Deck& d) : deck(d) { rng = std::mt19937{ std::random_device{}() };}
        int getBetAmount() { return currentBet.amount; }
        BaccaratPhase getPhase() { return phase; }
        bool isRoundFinished() { return phase == BaccaratPhase::Finished; }
        std::string phaseToString(BaccaratPhase phase) 
        {
            switch (phase) 
            {
                case BaccaratPhase::Betting: return "PHASE: BETTING";
                case BaccaratPhase::DealingInitial: return "PHASE: DEALING";
                case BaccaratPhase::PlayerThirdCard: return "PHASE: RESOLVING";
                case BaccaratPhase::BankerThirdCard: return "PHASE: RESOLVING";
                case BaccaratPhase::Resolve: return "PHASE: RESOLVING";
                default: return "";
            }
        }
        Card drawCard() { return deck.drawCardFromDeck(); }
        void startRound() 
        {
            playerHand.clear();
            bankerHand.clear();
            phase = BaccaratPhase::Betting;
            phaseTimer = 0.f;
        }
        bool isBettingOpen() { return phase == BaccaratPhase::Betting; }
        void placeBet(BetTarget target, int amount)
        {
            if (phase != BaccaratPhase::Betting) return;

            currentBet.target = target;
            currentBet.amount += amount;
        }
        void closeBetting() { phase = BaccaratPhase::DealingInitial; }
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
            if (playerHand.getThirdCard() == nullptr) { phase = BaccaratPhase::Resolve; return; } // check for if player did not draw a third card
            if (!doesBankerDrawAThirdCard(bankerHand, *playerHand.getThirdCard())) { phase = BaccaratPhase::Resolve; return; } // check for if banker should not draw a third card
            if (phaseTimer >= 0.5f) // if banker does draw a third card then draw the card and continue to resolve phase
            {
                bankerHand.addCard(drawCard());
                phase = BaccaratPhase::Resolve;
            }
        }
        int payout()
        {
            BaccaratResult winner = determineWinner(playerHand, bankerHand);

            int amount = 0;

            switch (currentBet.target)
            {
                case BetTarget::Player:
                    if (winner == BaccaratResult::Player)
                        amount = currentBet.amount * 2;
                    break;

                case BetTarget::Banker:
                    if (winner == BaccaratResult::Banker)
                        amount = static_cast<int>(currentBet.amount * 1.95);
                    break;

                case BetTarget::Tie:
                    if (winner == BaccaratResult::Tie)
                        amount = currentBet.amount * 9;
                    break;

                default:
                    break;
            }

            currentBet.amount = 0;
            currentBet.target = BetTarget::None;

            return amount;
        }
        std::string resultToString() 
        {
            if (phase != BaccaratPhase::Finished) return "";
            switch (determineWinner(playerHand, bankerHand)) 
            {
                case BaccaratResult::Banker: return "Banker Wins";
                case BaccaratResult::Player: return "Player Wins";
                case BaccaratResult::Tie: return "Tie Game";
                default: return "";
            }
        }
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