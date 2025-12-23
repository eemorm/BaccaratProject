#pragma once

// SFML
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Light
{
    public:
        Light(sf::Vector2f p, float r, float i, sf::Color c, bool f) { position = p; radius = r; baseIntensity = i; intensity = i; color = c; flicker = f; }
        ~Light() {}
        sf::Vector2f position;
        float radius;
        bool flicker;
        float baseIntensity;
        float intensity;
        float flickerDifference = 0.01f;
        float flickerTimer = 0.f;
        float flickerInterval = 0.1f;
        sf::Color color;
};