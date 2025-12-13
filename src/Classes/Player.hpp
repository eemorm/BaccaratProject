#pragma once

// Custom Includes
#include "Chip.hpp"

// SFML
#include <SFML/Graphics.hpp>

// Standard Libraries
#include <iostream>
#include <vector>

class Player
{
    private:
        std::vector<std::unique_ptr<Chip>> heldChips;
    public:
        std::vector<std::unique_ptr<Chip>>& getHeldChips() { return heldChips; }
        void setHeldChips(std::vector<std::unique_ptr<Chip>> hc) { heldChips = std::move(hc); }
        void clearHeldChips() { heldChips.clear(); }
};