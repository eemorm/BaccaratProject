#pragma once

// Custom Includes
#include "../textures.hpp"
#include "Card.hpp"

// SFML
#include <SFML/Graphics.hpp>

// Standard Libraries
#include <iostream>
#include <random>

class Deck : public sf::Drawable
{
    private:
        sf::Sprite sprite;
        sf::Sprite& background;
        std::vector<sf::Sprite>& numbers;
        std::vector<sf::Sprite>& suits;
        sf::Sprite& backside;

        std::vector<Card> deck;
        std::mt19937 rng;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
            target.draw(sprite, states);
        }
    public:
        Deck(sf::Sprite sp,
            sf::Sprite& bg,
            std::vector<sf::Sprite>& n,
            std::vector<sf::Sprite>& s,
            sf::Sprite& bs)
            : sprite(sp), background(bg), numbers(n), suits(s), backside(bs)
        {
            rng = std::mt19937{std::random_device{}()};
            deck.clear();
            for (int i = 0; i < suits.size(); i++)
            {
                for (int j = 0; j < numbers.size(); j++)
                {
                    Card card(background,
                    numbers[j],
                    suits[i],
                    backside,
                    sf::Color::White,
                    sf::Color::White,
                    sf::Color::White,
                    sf::Color::White,
                    j + 1);
                    deck.push_back(card);
                }
            }
        }
        sf::Vector2f getPosition() { return sprite.getPosition(); }
        void setPosition(sf::Vector2f p) { sprite.setPosition(p); }
        void addCard(Card& card) { deck.push_back(card); }
        void shuffleDeck() { std::shuffle(deck.begin(), deck.end(), rng); }
        void clearDeck() { deck.clear(); }
        Card drawCardFromDeck() 
        {
            Card c = deck.back();
            deck.pop_back();
            return c;
        }
};