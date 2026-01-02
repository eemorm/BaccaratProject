#pragma once

// Standard Libraries
#include <iostream>
#include <string>
#include <vector>

class TutorialController
{
    private:
        bool active = false;
        size_t step = 0;

        float stepTimer = 0.f;
        float stepDuration = 3.f;

        std::vector<std::string> steps
        {
            "Welcome.",
            "Before we begin, I want you to know that not everyone plays fair.",
            "That's just the way life is.",
            "I am not stopping to explain further. I don't have the time for this."
            "...",
            "First, you must bet.",
            "Place an amount of chips into a betting zone. Only one zone.",
            "...",
            "Don't be stupid, by the way. You can pick up a stack of chips.",
            "...",
            "Now, hit the confirm bet button to confirm and consume your bet.",
            "In the next phase, dealing, two cards will be dealt to both player and banker.",
            "The total is your score, after keeping only the last place of the score.",
            "Now, according to a specialized set of rules, third cards may be drawn.",
            "Lucky for you, you don't need to know these rules. Only I do.",
            "After final cards are drawn, the scores are totaled up according to the rule and whoever bet on the winner wins the payout.",
            "Ace is worth 1, face cards and 10 are worth 0, and all other cards are worth their number value.",
            "...",
            "Next, is the shop.",
            "You can look at and buy items that are useful in the next part, combat.",
            "To attack an enemy, you must first buy a weapon to do damage, and attacks so that you may gain the chance to attack.",
            "After doing so, you just have to click on an enemy to attack.",
            "Be careful though *for all I care* as enemies will automatically attack back as soon as one is hit.",
            "...",
            "By killing all the enemies, now you can choose an edge, which grants you a permanent buff.",
            "This permanent buff is crucial to your survival, so choose wisely.",
            "Now, after all of this, you have descended a floor in the complex, which is where we are now.",
            "Your goal is to keep getting further and further down, no matter what or who pushes against you.",
            "If you run out of money or health, well, I am afraid that your time has run out, as it may have already.",
            "Don't fear though, for now everything is controlled and restrained.",
            "But now our time is over.",
            "Good luck."
        };
    public:
        bool isActive() { return active; }
        void start() { active = true; step = 0; }
        void end() { active = false; }

        std::string& getText() { return steps[step]; }
        void nextStep()
        {
            step++;
            stepTimer = 0.f;
            if (step >= steps.size())
                active = false;
        }
        void update(float dt)
        {
            if (!active) return;

            stepTimer += dt;
            if (stepTimer >= stepDuration)
                nextStep();
        }
};