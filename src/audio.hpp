#pragma once

// SFML
#include <SFML/Audio.hpp>

// Standard Libraries
#include <vector>

std::vector<std::unique_ptr<sf::Music>> baccarat1;

inline void loadAudio()
{
    std::unique_ptr<sf::Music> m_Space = std::make_unique<sf::Music>();
    std::unique_ptr<sf::Music> m_sketch = std::make_unique<sf::Music>();
    std::unique_ptr<sf::Music> m_sketch2 = std::make_unique<sf::Music>();
    std::unique_ptr<sf::Music> m_daria = std::make_unique<sf::Music>();

    if (!m_Space->openFromFile("audio/music/SPACE.mp3")) { std::cout << "Failed to load audio file"; }
    if (!m_sketch->openFromFile("audio/music/sketch.mp3")) { std::cout << "Failed to load audio file"; }
    if (!m_sketch2->openFromFile("audio/music/sketch2.mp3")) { std::cout << "Failed to load audio file"; }
    if (!m_daria->openFromFile("audio/music/dariacore3.mp3")) { std::cout << "Failed to load audio file"; }

    m_Space->setLoop(true);
    m_Space->setVolume(50.f);

    m_sketch->setLoop(true);
    m_sketch->setVolume(50.f);

    m_sketch2->setLoop(true);
    m_sketch2->setVolume(50.f);

    m_daria->setLoop(true);
    m_daria->setVolume(50.f);

    baccarat1.push_back(std::move(m_Space));
    baccarat1.push_back(std::move(m_sketch));
    baccarat1.push_back(std::move(m_sketch2));
    baccarat1.push_back(std::move(m_daria));
}

inline void playRandom(std::vector<std::unique_ptr<sf::Music>>& tracks)
{
    if (tracks.empty()) return;
    int randomIndex = rand() % tracks.size();
    tracks[randomIndex]->play();
}