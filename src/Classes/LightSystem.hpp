#pragma once

// Custom Includes
#include "Light.hpp"

// SFML
#include <SFML/Graphics.hpp>

// Standard I/O
#include <iostream>
#include <vector>

class LightSystem : public sf::Drawable
{
    private:
        sf::RenderTexture mask;
        sf::Sprite maskSprite;
        
        std::vector<Light> staticLights;
        std::vector<Light> dynamicLights;

        sf::Texture softCircleTexture;
        sf::Sprite softCircleSprite;

        void createSoftCircleTexture(int size)
        {
            sf::Image img;
            img.create(size, size);

            sf::Vector2f center(size / 2.f, size / 2.f);
            float maxDist = size / 2.f;

            for (int y = 0; y < size; y++)
            {
                for (int x = 0; x < size; x++)            // TODO: understand ts
                {
                    float dx = x - center.x;
                    float dy = y - center.y;
                    float dist = std::sqrt(dx*dx + dy*dy);

                    float v = 1.0f - (dist / maxDist); 
                    if (v < 0) v = 0;

                    sf::Uint8 brightness = static_cast<sf::Uint8>(255 * v);

                    img.setPixel(x, y, sf::Color(brightness, brightness, brightness));
                }
            }

            softCircleTexture.loadFromImage(img);
            softCircleTexture.setSmooth(true);
        }
    public:
        LightSystem(int width, int height)
        {
            mask.create(width, height);
            maskSprite.setTexture(mask.getTexture());

            createSoftCircleTexture(512);
            softCircleSprite.setTexture(softCircleTexture);
            softCircleSprite.setOrigin(256, 256);
        }
        void addStaticLight(const Light& light) { staticLights.push_back(light); }
        void addDynamicLight(const Light& light) { dynamicLights.push_back(light); }
        void clearStaticLights() { staticLights.clear(); }
        void clearDynamicLights() { dynamicLights.clear(); }
        void update()
        {
            mask.clear(sf::Color::Black);

            auto drawLight = [&](const Light& l)
            {
                softCircleSprite.setPosition(l.position);
                float scale = (l.radius * 2.f) / 512.f;
                softCircleSprite.setScale(scale, scale);

                sf::Color c = l.color;
                c.a = static_cast<sf::Uint8>(255 * l.intensity);
                softCircleSprite.setColor(c);

                mask.draw(softCircleSprite, sf::BlendAdd);
            };

            for (const auto& l : staticLights)  drawLight(l);
            for (const auto& l : dynamicLights) drawLight(l);

            mask.display();
        }
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override 
        {
            target.draw(maskSprite, sf::BlendMultiply);
        }
};