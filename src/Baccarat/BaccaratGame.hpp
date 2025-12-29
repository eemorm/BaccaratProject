#pragma once

// Custom Includes
#include "BaccaratHand.hpp"
#include "../Classes/Deck.hpp"
#include "../Classes/Card.hpp"

// Standard Libraries
#include <vector>
#include <random>
#include <optional>

enum class BetTarget
{
    None,
    Player,
    Banker,
    Tie
};
enum class BaccaratResult 
{
    Player,
    Banker,
    Tie
};
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

class BaccaratGame
{
    private:
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

        BaccaratHand& getPlayerHand() { return playerHand; }
        BaccaratHand& getBankerHand() { return bankerHand; }
        int getBetAmount() { return currentBet.amount; }
        BaccaratPhase getGamePhase() { return phase; }

        Card drawCard() { return deck.drawCardFromDeck(); }
        void startRound() 
        {
            playerHand.clear();
            bankerHand.clear();
            phase = BaccaratPhase::Betting;
            phaseTimer = 0.f;
        }
        void placeBet(BetTarget target, int amount)
        {
            if (phase != BaccaratPhase::Betting) return;

            currentBet.target = target;
            currentBet.amount += amount;
        }
        void lockBetZones(BetTarget& target, sf::FloatRect& b, sf::FloatRect& t, sf::FloatRect& p)
        {
            switch (target)
            {
                case BetTarget::Player:
                    b.width = b.height = 0; t.width = t.height = 0;
                    break;
                case BetTarget::Banker:
                    p.width = p.height = 0; t.width = t.height = 0;
                    break;
                case BetTarget::Tie:
                    p.width = p.height = 0; b.width = b.height = 0;
                    break;
                default: 
                    break;
            }
        }
        void closeBetting() { phase = BaccaratPhase::DealingInitial; }
        bool doesPlayerDrawAThirdCard(BaccaratHand& player) { return player.total() <= 5; }
        bool doesBankerDrawAThirdCard(BaccaratHand& banker, Card playerThirdCard) 
        {
            int total = banker.total();

            if (total <= 2) return true;
            if (total == 3 && playerThirdCard.getValue() != 8) return true;
            if (total == 4 && (playerThirdCard.getValue() >= 2 && playerThirdCard.getValue() <= 7)) return true;
            if (total == 5 && (playerThirdCard.getValue() >= 4 && playerThirdCard.getValue() <= 7)) return true;
            if (total == 6 && (playerThirdCard.getValue() == 6 || playerThirdCard.getValue() == 7)) return true;
            return false;
        }
        BaccaratResult determineWinner(BaccaratHand& player, BaccaratHand& banker) 
        {
            int playerTotal = player.total();
            int bankerTotal = banker.total();
            if (playerTotal > bankerTotal) { return BaccaratResult::Player; }
            if (bankerTotal > playerTotal) { return BaccaratResult::Banker; }
            return BaccaratResult::Tie;
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
            {
                if (playerHand.total() >= 8 || bankerHand.total() >= 8)
                {
                    phase = BaccaratPhase::Resolve;
                    return;
                }
                phase = BaccaratPhase::PlayerThirdCard;
            }
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
            int bankerTotal = bankerHand.total();

            if (playerHand.getThirdCard() == nullptr)
            {
                if (bankerTotal <= 5 && phaseTimer >= 0.5f)
                    bankerHand.addCard(drawCard());

                phase = BaccaratPhase::Resolve;
                return;
            }

            if (doesBankerDrawAThirdCard(bankerHand, *playerHand.getThirdCard()))
            {
                if (phaseTimer >= 0.5f)
                    bankerHand.addCard(drawCard());
            }

            phase = BaccaratPhase::Resolve;
        }
        int payout()
        {
            BaccaratResult winner = determineWinner(playerHand, bankerHand);

            int amount = 0;

            switch (currentBet.target)
            {
                case BetTarget::Player:
                    if (winner == BaccaratResult::Player)
                        amount = currentBet.amount * 19;
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