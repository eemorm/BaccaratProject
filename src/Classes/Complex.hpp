#pragma once

// Custom Includes
#include "Enemy.hpp"
#include "EnemyDatabase.hpp"

// SFML
#include <SFML/Graphics.hpp>

// Standard Libraries
#include <iostream>
#include <string>
#include <vector>
#include <random>

class Complex
{
    private:
        std::string dealerName;
        sf::Sprite dealerSprite;

        std::vector<EnemyData*> enemyPool = 
        {
            &EnemyDB::Rat,
            &EnemyDB::Thug,
            &EnemyDB::Guard
        };
        std::vector<std::unique_ptr<Enemy>> currentEnemies;

        int floor = 0;
    public:
        Complex() {}
        std::vector<std::unique_ptr<Enemy>>& getCurrentEnemies() { return currentEnemies; }
        std::unique_ptr<Enemy> spawnEnemyFromTemplate(EnemyData* data, int floorLevel) 
        {
            auto scaledData = std::make_unique<EnemyData>(*data);

            scaledData->maxHealth += floorLevel * 5;    
            scaledData->attackDamage += floorLevel * 2;
            scaledData->armorValue += floorLevel;

            return std::make_unique<Enemy>(std::move(scaledData));
        }

        void spawnEnemiesForFloor() 
        {
            currentEnemies.clear();

            std::random_device rd;
            std::mt19937 rng(rd());
            std::uniform_int_distribution<int> dist(0, enemyPool.size() - 1);

            int numEnemies = std::min(floor + 2, 5); // example: 2 enemies at floor 0, +1 per floor, max 5

            for (int i = 0; i < numEnemies; i++) 
            {
                EnemyData* templateData = enemyPool[dist(rng)];
                auto enemy = spawnEnemyFromTemplate(templateData, floor);

                enemy->setPosition({ 300.f + i * 60.f, 300.f });
                currentEnemies.push_back(std::move(enemy));
            }
        }
        void nextFloor() { floor += 1; spawnEnemiesForFloor(); }
};