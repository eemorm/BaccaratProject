#pragma once

// Custom Includes
#include "UIElement.hpp"

// Standard Libraries
#include <vector>
#include <memory>

class UIManager 
{
    private:
        std::vector<std::unique_ptr<UIElement>> elements;
    public:
        const std::vector<std::unique_ptr<UIElement>>& getElements() const { return elements; }

        template<typename T, typename... Args>
        T& add(Args&&... args) 
        {
            auto element = std::make_unique<T>(std::forward<Args>(args)...);
            T& ref = *element;
            elements.push_back(std::move(element));
            return ref;
        }
        void handleEvent(sf::Event& event, sf::Vector2f& mouse) 
        {
            for (auto& el : elements)
                el->handleEvent(event, mouse);
        }
        void update(float dt) 
        {
            for (auto& el : elements)
                el->update(dt);
        }
        void draw(sf::RenderTarget& target, sf::RenderStates states)
        {
            for (auto& el : elements)
                el->draw(target, states);
        }
};