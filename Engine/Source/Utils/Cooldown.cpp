#include "Utils/Cooldown.h"

Cooldown::Cooldown(sf::Time duration)
    : m_duration(duration)
{}

Cooldown::~Cooldown() {}

void Cooldown::Start()
{
    m_timer.start();
}

void Cooldown::Stop()
{
    m_timer.stop();
}

void Cooldown::Restart()
{
    m_timer.restart();
}

void Cooldown::Reset()
{
    m_timer.reset();
}

bool Cooldown::IsRunning() const
{
    return m_timer.isRunning();
}

bool Cooldown::IsOver() const
{
    return GetElapsedTime() > m_duration;
}

sf::Time Cooldown::GetElapsedTime() const
{
    return m_timer.getElapsedTime();
}

float Cooldown::GetElapedTimeInSec() const
{
    return m_timer.getElapsedTime().asSeconds();
}

float Cooldown::getDuration() const
{
    return m_duration.asSeconds();
}

void Cooldown::setDuration(sf::Time newDuration)
{
    m_duration = newDuration;
}
