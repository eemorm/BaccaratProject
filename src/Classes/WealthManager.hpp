#pragma once

// Custom Includes
#include "ChipStack.hpp"
#include "../textures.hpp"

// Standard Libraries
#include <vector>

class WealthManager : public sf::Drawable
{
    private:
        std::vector<ChipStack*> stacks;
        int totalWealth = 0;

        void distributeChips() // greedy algorithm to distribute chips across stacks based on their denominations
        {
            int remaining = totalWealth;

            std::sort(stacks.begin(), stacks.end(), [](ChipStack* a, ChipStack* b) { return a->getChipValue() > b->getChipValue(); });

            for (auto& stack : stacks)
            {
                int numChips = remaining / stack->getChipValue();
                remaining -= numChips * stack->getChipValue();

                stack->clear();
                for (int i = 0; i < numChips; ++i)
                    stack->addChip(theDealerBackground);
            }
        }
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
            for (auto& stack : stacks)
                target.draw(*stack, states);
        }
    public:
        std::vector<ChipStack*> getStacks() { return stacks; }
        void addStack(ChipStack* stack, int denomination) { stack->setChipValue(denomination); stacks.push_back(stack); }
        void setWealth(int wealth) { totalWealth = wealth; distributeChips(); }
        void addWealth(int amount) { totalWealth += amount; distributeChips(); }
        int getWealth() { return totalWealth; }
};
