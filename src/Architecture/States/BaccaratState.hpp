// Custom Includes
#include "../../textures.hpp"
#include "../GameState.hpp"
#include "../../Classes/Card.hpp"
#include "../../Classes/ChipStack.hpp"
#include "../../Classes/Interfaces/IObjectAction.hpp"
#include "../../Classes/LightSystem.hpp"

// SFML
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// Standard Libraries
#include <iostream>
#include <vector>

class BaccaratState : public GameState
{
    private:
        sf::RenderWindow& window;

        

    public:
        BaccaratState(sf::RenderWindow& w) : window(w) {}

        void handleEvent(sf::Event& event) override;
        void update(float dt) override;
        void draw(sf::RenderWindow& window) override;
};
