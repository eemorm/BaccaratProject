#pragma once

// Custom Includes
#include "../Card.hpp"
#include "BaccaratHand.hpp"
#include "BaccaratResult.hpp"

inline bool doesPlayerDrawAThirdCard(BaccaratHand& player) { return player.total() <= 5; }
inline bool doesBankerDrawAThirdCard(BaccaratHand& banker, Card playerThirdCard) 
{
    int total = banker.total();

    if (total <= 2) return true;
    if (total == 3 && playerThirdCard.getValue() != 8) return true;
    if (total == 4 && (playerThirdCard.getValue() >= 2 && playerThirdCard.getValue() <= 7)) return true;
    if (total == 5 && (playerThirdCard.getValue() >= 4 && playerThirdCard.getValue() <= 7)) return true;
    if (total == 6 && (playerThirdCard.getValue() == 6 || playerThirdCard.getValue() == 7)) return true;
    return false;
}
inline BaccaratResult determineWinner(BaccaratHand& player, BaccaratHand& banker) 
{
    int playerTotal = player.total();
    int bankerTotal = banker.total();
    if (playerTotal > bankerTotal) { return BaccaratResult::Player; }
    if (bankerTotal > playerTotal) { return BaccaratResult::Banker; }
    return BaccaratResult::Tie;
}
