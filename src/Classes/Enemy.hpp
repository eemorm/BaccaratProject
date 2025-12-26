#pragma once

// SFML
#include <SFML/Graphics.hpp>

// Standard Libraries
#include <memory>

struct EnemyData
{
    std::string name;
    int maxHealth;
    int armorValue;
    int attackDamage;
    int level;
    sf::Color color;
};
class Enemy : public sf::Drawable
{
    private:
        std::unique_ptr<EnemyData> data;

        int currentHealth;
        sf::RectangleShape body;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
            target.draw(body, states);
        }
    public:
        Enemy(std::unique_ptr<EnemyData> d) : data(std::move(d))
        {
            body.setSize({40.f, 40.f});
            body.setFillColor(data->color);
            currentHealth = data->maxHealth;
        }
        sf::RectangleShape& getBody() { return body; }
        void setPosition(sf::Vector2f pos) { body.setPosition(pos); }
        int getAttackDamage() { return data->attackDamage; }
        int getCurrentHealth() { return currentHealth; }
        virtual void takeDamage(int damage) { int finalDamage = std::max(0, damage - data->armorValue); currentHealth -= finalDamage; }
        bool isDead() { return currentHealth <= 0; }
};