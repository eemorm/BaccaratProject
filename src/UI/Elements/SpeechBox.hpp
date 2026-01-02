#pragma once

// Custom Includes
#include "../../textures.hpp"

// SFML
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <sstream>

class SpeechBox : public sf::Drawable
{
private:
    sf::RectangleShape body;
    sf::Text text;

    float padding = 12.f;
    float maxWidth = 300.f;  
    float charSpeed = 50.f;  

    std::string fullText;       // fully wrapped text
    size_t displayedChars = 0;  // how many characters to show for typing effect
    float charTimer = 0.f;      // timer for typing effect

    std::vector<std::string> wrappedLines; // store lines for height calculation

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(body, states);
        target.draw(text, states);
    }

    // Wrap text and store lines
    void wrapText(const std::string& str)
    {
        wrappedLines.clear();
        std::istringstream words(str);
        std::string word;
        std::string line;

        while (words >> word)
        {
            std::string testLine = line.empty() ? word : line + " " + word;
            text.setString(testLine);
            if (text.getLocalBounds().width + padding * 2 > maxWidth)
            {
                if (!line.empty()) wrappedLines.push_back(line);
                line = word;
            }
            else
            {
                line = testLine;
            }
        }
        if (!line.empty()) wrappedLines.push_back(line);

        // Combine lines into fullText with line breaks
        fullText.clear();
        for (size_t i = 0; i < wrappedLines.size(); ++i)
        {
            fullText += wrappedLines[i];
            if (i + 1 < wrappedLines.size()) fullText += "\n";
        }

        // Resize box based on number of lines and max line width
        float maxLineWidth = 0.f;
        for (const auto& l : wrappedLines)
        {
            text.setString(l);
            float w = text.getLocalBounds().width;
            if (w > maxLineWidth) maxLineWidth = w;
        }

        body.setSize({ maxLineWidth + padding * 2, wrappedLines.size() * text.getCharacterSize() * 1.2f + padding * 2 });
        text.setPosition(body.getPosition().x + padding, body.getPosition().y + padding);

        // Reset typing effect
        displayedChars = 0;
        charTimer = 0.f;
        text.setString("");
    }

    void updateText()
    {
        text.setString(fullText.substr(0, displayedChars));
    }

public:
    SpeechBox()
    {
        text.setFont(font); 
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(16);
        text.setStyle(sf::Text::Bold);

        body.setFillColor(sf::Color(50, 50, 50, 220));
        body.setOutlineColor(sf::Color::White);
        body.setOutlineThickness(2.f);
        body.setSize({200.f, 50.f});
    }

    // Set the text to show in the speech bubble
    void setText(const std::string& str)
    {
        wrapText(str);
    }

    // Set anchor at top-left
    void setAnchor(const sf::Vector2f& topLeftAnchor)
    {
        body.setPosition(topLeftAnchor);
        text.setPosition(body.getPosition().x + padding, body.getPosition().y + padding);
    }

    // Update typing effect
    void update(float dt)
    {
        if (displayedChars >= fullText.size()) return;

        charTimer += dt * charSpeed;
        size_t charsToShow = static_cast<size_t>(charTimer);
        if (charsToShow > fullText.size()) charsToShow = fullText.size();
        displayedChars = charsToShow;

        updateText();
    }

    void setMaxWidth(float width) { maxWidth = width; }
};