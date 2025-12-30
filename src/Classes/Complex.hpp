#pragma once

// Custom Includes
#include "../audio.hpp"
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
            &EnemyDB::Insect,
            &EnemyDB::Rat,
            &EnemyDB::Reaper,
            &EnemyDB::Thug,
            &EnemyDB::Guard,
            &EnemyDB::Executioner
        };
        std::vector<std::unique_ptr<Enemy>> currentEnemies;

        int floor = 1;
    public:
        Complex() {}
        std::vector<std::unique_ptr<Enemy>>& getCurrentEnemies() { return currentEnemies; }
        int getFloor() { return floor; }
        std::unique_ptr<Enemy> spawnEnemyFromTemplate(EnemyData* data, int floorLevel) 
        {
            auto scaledData = std::make_unique<EnemyData>(*data);

            int scaledFloor = floor - 1;

            scaledData->maxHealth += scaledFloor * 5;    
            scaledData->attackDamage += scaledFloor * 2;
            scaledData->armorValue += scaledFloor;

            return std::make_unique<Enemy>(std::move(scaledData));
        }

        void spawnEnemiesForFloor() 
        {
            currentEnemies.clear();

            std::random_device rd;
            std::mt19937 rng(rd());

            std::vector<EnemyData*> candidates;

            for (auto& enemy : enemyPool)
            {
                if (enemy->minFloor <= floor)
                    candidates.push_back(enemy);
            }

            std::shuffle(candidates.begin(), candidates.end(), rng);

            int numEnemies = std::min(floor + 1, 5); 

            std::uniform_int_distribution<int> dist(0, candidates.size() - 1);

            for (int i = 0; i < numEnemies; i++) 
            {
                EnemyData* templateData = candidates[dist(rng)];
                auto enemy = spawnEnemyFromTemplate(templateData, floor);

                enemy->setPosition({ 300.f + i * 60.f, 300.f });
                currentEnemies.push_back(std::move(enemy));
            }
        }
        void nextFloor() { floor += 1; spawnEnemiesForFloor(); stopAllMusic(); playRandom(baccarat1); }
};