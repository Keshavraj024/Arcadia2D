#pragma once

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

class TimeManager {
  public:
    float GetDeltaTime() const;
    float GetElapsedTime() const;

    void Update();

  private:
    sf::Time m_deltaTime; // Time diff between frames
    sf::Clock m_clock; // Total elapsed time from engine started
    sf::Time m_prevTime; // time to store the occurrence of previous frame
};
