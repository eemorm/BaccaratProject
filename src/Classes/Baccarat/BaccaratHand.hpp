#pragma once

// Custom Includes
#include "../Card.hpp"

// Standard Libraries
#include <vector>

class BaccaratHand 
{
    private:
        std::vector<Card> cards;
    public:
        std::vector<Card>& getCards() { return cards; }
        int total() 
        {
            int sum = 0;
            for (auto& c : cards) sum += c.getValue();
            return sum % 10;
        }
        void addCard(Card card) { cards.push_back(card); }
        void clear() { cards.clear(); }
        Card* getThirdCard() { if (cards.size() >= 3) return &cards[2]; return nullptr; }
};
