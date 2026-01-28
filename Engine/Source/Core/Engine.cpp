#include "Core/Engine.h"
#include "Core/EngineConfig.h"
#include "Utils/Log.h"

Engine::Engine() : m_window(sf::VideoMode(sf::Vector2u{gEngineConfig.windowSize}), gEngineConfig.windowTitle)
{
  m_window.setIcon(sf::Image("Content/Textures/windowIcon.png"));
  m_window.setMinimumSize(m_window.getSize() / 2u);

  if(gEngineConfig.disableSfmlLogs) {
    sf::err().rdbuf(nullptr);
  }


  LOG_INFO("WINDOW IS CREATED");

  m_engineContext.save.Set("score", 42);
}

bool Engine::IsRunning() const
{
  return m_window.isOpen();
}

void Engine::ProcessEvents()
{
  while(const auto event = m_window.pollEvent()) {
    event->visit(EngineVisitor{*this});
  }
}

void Engine::Update()
{
  m_engineContext.time.Update();
}

void Engine::Render()
{
  m_window.clear();


  m_window.display();
}


void Engine::EngineWindowClose()
{
  m_window.close();
  LOG_INFO("WINDOW CLOSED {:.2f} ", m_engineContext.time.GetElapsedTime());
}

void Engine::EngineWindowResize(const sf::Vector2u& windowSize)
{
  LOG_INFO("WINDOW SIZE RESIZED X: {} Y: {}", windowSize.x, windowSize.y);
}

void Engine::EngineWindowFocusLost()
{
  LOG_INFO("WINDOW FOCUS LOST");
}

void Engine::EngineWindowFocusGain()
{
  LOG_INFO("WINDOW FOCUS GAIN");
}
