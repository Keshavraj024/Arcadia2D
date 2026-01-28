#include <algorithm>

#include "Managers/TimeManager.h"
#include "Core/EngineConfig.h"

void TimeManager::Update() {
  const auto currentTime = m_clock.getElapsedTime();
  // to make sure deltatime value is not huge when the screen is hung
  m_deltaTime = std::min(currentTime - m_prevTime, gEngineConfig.maxDeltaTime);
  m_prevTime = currentTime;
}

float TimeManager::GetDeltaTime() const
{
  return m_deltaTime.asSeconds();
}

float TimeManager::GetElapsedTime() const
{
  return m_clock.getElapsedTime().asSeconds();
}
