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

        ChipStack stack100;
        ChipStack stack50;
        ChipStack stack10;
        ChipStack stack1;

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
        WealthManager() 
        : stack100({55, 639}, 100),
          stack50({155, 639}, 50),
          stack10({255, 639}, 10),
          stack1({355, 639}, 1)
        {}

        void initializeManager()
        {
            stacks.push_back(&stack100);
            stacks.push_back(&stack50);
            stacks.push_back(&stack10);
            stacks.push_back(&stack1);
        }
        std::vector<ChipStack*> getStacks() { return stacks; }
        void addStack(ChipStack* stack, int denomination) { stack->setChipValue(denomination); stacks.push_back(stack); }
        void setWealth(int wealth) { totalWealth = wealth; distributeChips(); }
        void addWealth(int amount) { totalWealth += amount; distributeChips(); }
        int getWealth() { return totalWealth; }
};
