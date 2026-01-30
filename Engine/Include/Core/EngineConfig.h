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
    float cursorSpeed;
    float cursorRadius;
    sf::Color cursorColor;
    float joystickDeadzone;
    bool cursorVisibility;

    std::string guiTheme;
    std::string guiFont;

    EngineConfig();
};

inline const EngineConfig gEngineConfig;
