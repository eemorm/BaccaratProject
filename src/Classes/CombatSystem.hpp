#pragma once

// Custom Includes
#include "Enemy.hpp"
#include "PlayerCombat.hpp"
#include "Complex.hpp"

// SFML
#include <SFML/Graphics.hpp>

enum class CombatState
{
    Idle,
    PlayerTurn,
    EnemyTurn,
    Resolving
};

class CombatSystem
{
    private:
        CombatState state = CombatState::Idle;

        Complex* complex;
        PlayerCombat* player;

        void playerAttack(Enemy& enemy)
        {
            int damage = player->getAttackDamage();
            if (player->getPlayerInventory().getAttacks() > 0)
            {
                enemy.takeDamage(damage);
                player->getPlayerInventory().useAttack();
            }
        }
        void enemiesAttack()
        {
            for (auto& enemy : complex->getCurrentEnemies())
            {
                int enemyDamage = enemy->getAttackDamage();
                player->takeDamage(enemyDamage);
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
        CombatSystem(Complex* c, PlayerCombat* p) : complex(c), player(p) {}
        void handlePlayerClick(sf::Vector2f mousePos)
        {
            if (state != CombatState::Idle)
                return;

            for (auto& enemy : complex->getCurrentEnemies())
            {
                if (enemy->getBody().getGlobalBounds().contains(mousePos) && player->getPlayerInventory().getAttacks() > 0)
                {
                    playerAttack(*enemy);
                    state = CombatState::EnemyTurn;
                    break;
                }
            }
        }
        void update()
        {
            switch (state)
            {
                case CombatState::EnemyTurn:
                    enemiesAttack();
                    cleanupDeadEnemies();
                    state = CombatState::Idle;
                    break;
                default:
                    break;
            }
        }
};
