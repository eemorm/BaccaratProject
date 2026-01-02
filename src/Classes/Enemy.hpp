#pragma once

// SFML
#include <SFML/Graphics.hpp>

// Standard Libraries
#include <memory>

struct EnemyData
{
    sf::Texture* texture;
    std::string name;
    int maxHealth;
    int armorValue;
    int attackDamage;
    int level;
    int minFloor;
};
class Enemy : public sf::Drawable
{
    private:
        std::unique_ptr<EnemyData> data;
        sf::Sprite sprite;

        int currentHealth;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
            target.draw(sprite, states);
        }
    public:
        Enemy(std::unique_ptr<EnemyData> d) : data(std::move(d))
        {
            sprite.setTexture(*data->texture);
            sprite.setScale(3.f, 3.f);
            currentHealth = data->maxHealth;
        }
        std::unique_ptr<EnemyData>& getData() { return data; }
        sf::Sprite getSprite() { return sprite; }
        void setPosition(sf::Vector2f pos) { sprite.setPosition(pos); }
        int getAttackDamage() { return data->attackDamage; }
        int getCurrentHealth() { return currentHealth; }
        int getMaxHealth() { return data->maxHealth; }
        virtual void takeDamage(int damage) { int finalDamage = std::max(0, damage - data->armorValue / 2); currentHealth -= finalDamage; }
        bool isDead() { return currentHealth <= 0; }
};