#pragma once

// SFML
#include <SFML/Audio.hpp>

// Standard Libraries
#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>

// Music
inline std::vector<std::unique_ptr<sf::Music>> baccarat1;

// SFX
inline std::vector<std::unique_ptr<sf::SoundBuffer>> cardDrawBuffers;
inline std::vector<std::unique_ptr<sf::SoundBuffer>> shuffleBuffers;
inline std::vector<std::unique_ptr<sf::SoundBuffer>> buttonPressBuffers;
inline std::vector<std::unique_ptr<sf::SoundBuffer>> buttonReleaseBuffers;

inline std::vector<std::unique_ptr<sf::Sound>> cardDrawSounds;
inline std::vector<std::unique_ptr<sf::Sound>> shuffleSounds;
inline std::vector<std::unique_ptr<sf::Sound>> buttonPressSounds;
inline std::vector<std::unique_ptr<sf::Sound>> buttonReleaseSounds;

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
    std::unique_ptr<sf::Music> m_sketch = std::make_unique<sf::Music>();
    std::unique_ptr<sf::Music> m_sketch2 = std::make_unique<sf::Music>();
    std::unique_ptr<sf::Music> m_daria = std::make_unique<sf::Music>();
    std::unique_ptr<sf::Music> m_ca2 = std::make_unique<sf::Music>();

    if (!m_Space->openFromFile("audio/music/SPACE.mp3")) { std::cout << "Failed to load audio file"; }
    if (!m_sketch->openFromFile("audio/music/sketch.mp3")) { std::cout << "Failed to load audio file"; }
    if (!m_sketch2->openFromFile("audio/music/sketch2.mp3")) { std::cout << "Failed to load audio file"; }
    if (!m_daria->openFromFile("audio/music/dariacore3.mp3")) { std::cout << "Failed to load audio file"; }
    if (!m_ca2->openFromFile("audio/music/CA2.mp3")) { std::cout << "Failed to load audio file"; }

    m_Space->setLoop(true);
    m_Space->setVolume(10.f);

    m_sketch->setLoop(true);
    m_sketch->setVolume(10.f);

    m_sketch2->setLoop(true);
    m_sketch2->setVolume(10.f);

    m_daria->setLoop(true);
    m_daria->setVolume(10.f);
    
    m_ca2->setLoop(true);
    m_ca2->setVolume(10.f);

    baccarat1.push_back(std::move(m_Space));
    //baccarat1.push_back(std::move(m_sketch));
    baccarat1.push_back(std::move(m_sketch2));
    baccarat1.push_back(std::move(m_daria));
    baccarat1.push_back(std::move(m_ca2));


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

    // --------------------
    // BUTTON PRESS
    // --------------------
    addSFX("audio/sfx/buttonpress1.wav", buttonPressBuffers, buttonPressSounds);
    addSFX("audio/sfx/buttonpress2.wav", buttonPressBuffers, buttonPressSounds);
    addSFX("audio/sfx/buttonpress3.wav", buttonPressBuffers, buttonPressSounds);
    addSFX("audio/sfx/buttonpress4.wav", buttonPressBuffers, buttonPressSounds);
    addSFX("audio/sfx/buttonpress5.wav", buttonPressBuffers, buttonPressSounds);
    addSFX("audio/sfx/buttonpress6.wav", buttonPressBuffers, buttonPressSounds);

    // --------------------
    // BUTTON RELEASE
    // --------------------
    addSFX("audio/sfx/buttonrelease1.wav", buttonReleaseBuffers, buttonReleaseSounds);
    addSFX("audio/sfx/buttonrelease2.wav", buttonReleaseBuffers, buttonReleaseSounds);
    addSFX("audio/sfx/buttonrelease3.wav", buttonReleaseBuffers, buttonReleaseSounds);
    addSFX("audio/sfx/buttonrelease4.wav", buttonReleaseBuffers, buttonReleaseSounds);
    addSFX("audio/sfx/buttonrelease5.wav", buttonReleaseBuffers, buttonReleaseSounds);
    addSFX("audio/sfx/buttonrelease6.wav", buttonReleaseBuffers, buttonReleaseSounds);
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
    for (auto& music : baccarat1)
    {
        if (music->getStatus() == sf::Music::Playing)
            music->stop();
    }
}