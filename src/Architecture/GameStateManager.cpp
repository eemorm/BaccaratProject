#include "GameStateManager.hpp"
#include "States/MainMenuState.hpp"
#include "States/BaccaratState.hpp"
#include "States/DeathState.hpp"

void GameStateManager::changeState(StateID id, sf::RenderWindow& window)
{
    switch (id)
    {
        case StateID::MainMenu:
            currentState = std::make_unique<MainMenuState>(window, this);
            break;
        case StateID::Baccarat:
            currentState = std::make_unique<BaccaratState>(window, this);
            break;
        case StateID::Death:
            currentState = std::make_unique<DeathState>(window, this);
            break;
    }
}

void GameStateManager::handleEvent(sf::Event& event) { if(currentState) currentState->handleEvent(event); }
void GameStateManager::update(float dt) { if(currentState) currentState->update(dt); }
void GameStateManager::draw(sf::RenderWindow& window) { if(currentState) currentState->draw(window); }