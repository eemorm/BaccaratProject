#pragma once

// SFML
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Light
{
    public:
        Light(sf::Vector2f p, float r, float i, sf::Color c) { position = p; radius = r; intensity = i; color = c; }
        ~Light() {}
        sf::Vector2f position;
        float radius;
        float intensity;
        sf::Color color;
};