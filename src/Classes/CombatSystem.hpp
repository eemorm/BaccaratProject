#pragma once

// Custom Includes
#include "Enemy.hpp"
#include "PlayerCombat.hpp"
#include "PlayerHealth.hpp"
#include "Complex.hpp"

// SFML
#include <SFML/Graphics.hpp>

// Standard Libraries
#include <iostream>

enum class CombatState
{
    Idle,
    EnemyAttack,
    EnemyPause
};

class CombatSystem
{
    private:
        CombatState state = CombatState::Idle;

        Complex* complex;
        PlayerCombat* playerCombat;
        PlayerHealth* playerHealth;

        sf::Clock turnClock;
        float pauseTime = 0.6f;
        size_t currentEnemy = 0;

        void playerAttack(Enemy& enemy)
        {
            int damage = playerCombat->getAttackDamage();
            if (playerCombat->getPlayerInventory().getAttacks() > 0)
            {
                enemy.takeDamage(damage);
                playerCombat->getPlayerInventory().useAttack();
            }
            if (complex->getCurrentEnemies().size() == 0)
            {
                state = CombatState::Idle;
            }
        }
        void enemiesAttack()
        {
            for (auto& enemy : complex->getCurrentEnemies())
            {
                int enemyDamage = enemy->getAttackDamage();
                playerHealth->takeDamage(enemyDamage, playerCombat->getArmorValue());
            }
        }
        void cleanupDeadEnemies()
        {
            auto& enemies = complex->getCurrentEnemies();
            enemies.erase(
                std::remove_if(enemies.begin(), enemies.end(),
                    [](std::unique_ptr<Enemy>& e) { return e->isDead(); }),
                enemies.end()
            );
        }
    public:
        CombatSystem(Complex* c, PlayerCombat* pc, PlayerHealth* ph) : complex(c), playerCombat(pc), playerHealth(ph) {}
        void handlePlayerClick(sf::Vector2f mousePos)
        {
            if (state != CombatState::Idle)
                return;

            Enemy* clickedEnemy = nullptr;

            for (auto& enemy : complex->getCurrentEnemies())
            {
                if (enemy->getSprite().getGlobalBounds().contains(mousePos) &&
                    playerCombat->getPlayerInventory().getAttacks() > 0)
                {
                    clickedEnemy = enemy.get();
                    break;
                }
            }

            if (clickedEnemy)
            {
                playerAttack(*clickedEnemy);
                cleanupDeadEnemies();

                currentEnemy = 0;
                state = CombatState::EnemyPause;
                turnClock.restart();
            }
        }
        void update()
        {
            switch (state)
            {
                case CombatState::EnemyPause:
                    if (turnClock.getElapsedTime().asSeconds() >= pauseTime)
                    {
                        state = CombatState::EnemyAttack;
                    }
                    break;

                case CombatState::EnemyAttack:
                {
                    auto& enemies = complex->getCurrentEnemies();

                    if (currentEnemy < enemies.size())
                    {
                        playerHealth->takeDamage(enemies[currentEnemy]->getAttackDamage(), playerCombat->getArmorValue());
                        currentEnemy++;

                        state = CombatState::EnemyPause;
                        turnClock.restart();
                    }
                    else
                    {
                        cleanupDeadEnemies();
                        state = CombatState::Idle;
                    }
                    break;
                }

                default:
                    break;
            }
        }
};
