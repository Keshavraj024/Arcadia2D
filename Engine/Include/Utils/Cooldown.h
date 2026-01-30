#pragma once

#include "SFML/System/Time.hpp"
#include <SFML/System/Clock.hpp>

class Cooldown
{
public:
    Cooldown(sf::Time duration = sf::seconds(0.f));
    ~Cooldown();

    void Start();
    void Stop();
    void Restart();
    void Reset();

    bool IsRunning() const;
    bool IsOver() const;

    sf::Time GetElapsedTime() const;
    float GetElapedTimeInSec() const;

    float getDuration() const;
    void setDuration(sf::Time newDuration);

private:
    sf::Clock m_timer;
    sf::Time m_duration;
};
