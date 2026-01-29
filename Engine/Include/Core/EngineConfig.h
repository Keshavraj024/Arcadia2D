#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

struct EngineConfig {

    sf::Vector2f windowSize {};
    std::string windowTitle {};
    bool disableSfmlLogs {};
    sf::Time maxDeltaTime {};
    float globalVolume;
    sf::Color backgroundColor;

    EngineConfig();
};

inline const EngineConfig gEngineConfig;
