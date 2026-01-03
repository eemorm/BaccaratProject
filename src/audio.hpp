#pragma once

// SFML
#include <SFML/Audio.hpp>

// Standard Libraries
#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>

// Music
inline std::unique_ptr<sf::Music> m_maintheme = std::make_unique<sf::Music>();
inline std::unique_ptr<sf::Music> m_falling = std::make_unique<sf::Music>();
inline std::vector<std::unique_ptr<sf::Music>> baccarat1;

// SFX
inline std::vector<std::unique_ptr<sf::SoundBuffer>> cardDrawBuffers;
inline std::vector<std::unique_ptr<sf::SoundBuffer>> shuffleBuffers;

inline std::vector<std::unique_ptr<sf::Sound>> cardDrawSounds;
inline std::vector<std::unique_ptr<sf::Sound>> shuffleSounds;

inline void addSFX(
    const std::string& path,
    std::vector<std::unique_ptr<sf::SoundBuffer>>& buffers,
    std::vector<std::unique_ptr<sf::Sound>>& sounds)
{
    auto buffer = std::make_unique<sf::SoundBuffer>();
    if (!buffer->loadFromFile(path))
        std::cout << "Failed to load " << path << "\n";

    auto sound = std::make_unique<sf::Sound>();
    sound->setBuffer(*buffer);

    sound->setVolume(100.f);

    buffers.push_back(std::move(buffer));
    sounds.push_back(std::move(sound));
}

inline void loadAudio()
{
    // Music
    std::unique_ptr<sf::Music> m_Space = std::make_unique<sf::Music>();
    std::unique_ptr<sf::Music> m_sketch2 = std::make_unique<sf::Music>();
    std::unique_ptr<sf::Music> m_daria = std::make_unique<sf::Music>();
    std::unique_ptr<sf::Music> m_ca2 = std::make_unique<sf::Music>();
    std::unique_ptr<sf::Music> m_dark2 = std::make_unique<sf::Music>();

    if (!m_maintheme->openFromFile("audio/music/maintheme.mp3")) { std::cout << "Failed to load audio file"; }
    if (!m_falling->openFromFile("audio/music/falling.mp3")) { std::cout << "Failed to load audio file"; }
    if (!m_Space->openFromFile("audio/music/SPACE.mp3")) { std::cout << "Failed to load audio file"; }
    if (!m_sketch2->openFromFile("audio/music/sketch2.mp3")) { std::cout << "Failed to load audio file"; }
    if (!m_daria->openFromFile("audio/music/dariacore3.mp3")) { std::cout << "Failed to load audio file"; }
    if (!m_ca2->openFromFile("audio/music/CA2.mp3")) { std::cout << "Failed to load audio file"; }
    if (!m_dark2->openFromFile("audio/music/dark2.mp3")) { std::cout << "Failed to load audio file"; }

    m_maintheme->setLoop(true);
    m_maintheme->setVolume(10.f);

    m_falling->setLoop(true);
    m_falling->setVolume(10.f);

    m_Space->setLoop(true);
    m_Space->setVolume(10.f);

    m_sketch2->setLoop(true);
    m_sketch2->setVolume(10.f);

    m_daria->setLoop(true);
    m_daria->setVolume(10.f);
    
    m_ca2->setLoop(true);
    m_ca2->setVolume(10.f);

    m_dark2->setLoop(true);
    m_dark2->setVolume(10.f);

    baccarat1.push_back(std::move(m_Space));
    baccarat1.push_back(std::move(m_sketch2));
    //baccarat1.push_back(std::move(m_daria));
    baccarat1.push_back(std::move(m_ca2));
    baccarat1.push_back(std::move(m_dark2));

    // SFX
    // --------------------
    // CARD DRAWS
    // --------------------
    addSFX("audio/sfx/carddraw1.wav", cardDrawBuffers, cardDrawSounds);
    addSFX("audio/sfx/carddraw2.wav", cardDrawBuffers, cardDrawSounds);
    addSFX("audio/sfx/carddraw3.wav", cardDrawBuffers, cardDrawSounds);
    addSFX("audio/sfx/carddraw4.wav", cardDrawBuffers, cardDrawSounds);
    addSFX("audio/sfx/carddraw5.wav", cardDrawBuffers, cardDrawSounds);

    // --------------------
    // SHUFFLES
    // --------------------
    addSFX("audio/sfx/shuffledeck1.wav", shuffleBuffers, shuffleSounds);
    addSFX("audio/sfx/shuffledeck2.wav", shuffleBuffers, shuffleSounds);
}

inline void playRandom(std::vector<std::unique_ptr<sf::Music>>& tracks)
{
    if (tracks.empty()) return;
    int randomIndex = rand() % tracks.size();
    tracks[randomIndex]->play();
}

inline void playRandom(std::vector<std::unique_ptr<sf::Sound>>& tracks)
{
    if (tracks.empty()) return;
    int randomIndex = rand() % tracks.size();
    tracks[randomIndex]->play();
}

inline void stopAllMusic()
{
    m_maintheme->stop();
    m_falling->stop();
    for (auto& music : baccarat1)
    {
        if (music->getStatus() == sf::Music::Playing)
            music->stop();
    }
}