#pragma once

// Custom Includes
#include "../textures.hpp"
#include "Edge.hpp"
#include "EdgeDatabase.hpp"

// SFML
#include <SFML/Graphics.hpp>

// Standard Libraries
#include <vector>
#include <algorithm>
#include <random>

class EdgeManager : public sf::Drawable
{
private:
    bool active = false;

    std::vector<Edge> pool =
    {
        EdgeDB::FleshShield,
        EdgeDB::BankersBuff,
        EdgeDB::TiedKnot,
        EdgeDB::PlayersBuff,
        EdgeDB::Monopoly,
        EdgeDB::Parasite,
        EdgeDB::YardSale,
        EdgeDB::BloodyKey
    };

    std::vector<Edge> edges;
    std::vector<sf::Text> texts;

    int selectedIndex = -1;

    std::mt19937 rng;

public:
    EdgeManager() : rng(std::random_device{}()) {}

    bool isOpen() const { return active; }
    bool hasSelection() const { return selectedIndex != -1; }
    Edge& getSelectedEdge() { return edges[selectedIndex]; }

    void initializeEdges()
    {
        edges.clear();
        texts.clear();
        selectedIndex = -1;

        std::shuffle(pool.begin(), pool.end(), rng);

        int count = std::min(3, (int)pool.size());
        edges.assign(pool.begin(), pool.begin() + count);
    }

    void open()
    {
        active = true;
        texts.clear();

        for (int i = 0; i < edges.size(); i++)
        {
            sf::Text t;
            t.setFont(font);
            t.setCharacterSize(26);
            t.setFillColor(sf::Color::White);

            t.setString(
                edges[i].name + "\n" +
                edges[i].description
            );

            t.setPosition(500.f, 240.f + i * 110.f);
            texts.push_back(t);
        }
    }

    void close()
    {
        active = false;
        texts.clear();
        selectedIndex = -1;
    }

    bool handleEvent(sf::Event& event, sf::Vector2f mouse)
    {
        if (!active) return false;

        for (int i = 0; i < texts.size(); i++)
        {
            bool hovered = texts[i].getGlobalBounds().contains(mouse);
            texts[i].setFillColor(hovered ? sf::Color::Yellow : sf::Color::White);

            if (hovered &&
                event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                selectedIndex = i;
                return true;
            }
        }
        return false;
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        if (!active) return;

        sf::RectangleShape dim({ 1600.f, 900.f });
        dim.setFillColor(sf::Color(0, 0, 0, 180));
        target.draw(dim, states);

        for (const auto& t : texts)
            target.draw(t, states);
    }
};