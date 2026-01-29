#include "Core/Engine.h"
#include "Core/EngineConfig.h"
#include "Utils/Log.h"

Engine::Engine() : m_window(sf::VideoMode(sf::Vector2u{gEngineConfig.windowSize}), gEngineConfig.windowTitle), m_engineContext(m_window)
{
  m_window.setIcon(sf::Image("Content/Textures/windowIcon.png"));
  m_window.setMinimumSize(m_window.getSize() / 2u);

  if(gEngineConfig.disableSfmlLogs) {
    sf::err().rdbuf(nullptr);
  }


  LOG_INFO("WINDOW IS CREATED");

  m_engineContext.audio.SetGlobalVolume(gEngineConfig.globalVolume);
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

  m_engineContext.renderer.BeginDrawing();

  m_window.draw(sf::Sprite(m_engineContext.renderer.FinishDrawing()));

  m_window.display();
}

void Engine::EventWindowClose()
{
    m_window.close();
    LOG_INFO("WINDOW CLOSED {:.2f} ", m_engineContext.time.GetElapsedTime());
}

void Engine::EventWindowResize(const sf::Vector2u &windowSize)
{
    LOG_INFO("WINDOW SIZE RESIZED X: {} Y: {}", windowSize.x, windowSize.y);
}

void Engine::EventWindowFocusLost()
{
    // LOG_INFO("WINDOW FOCUS LOST");
}

void Engine::EventWindowFocusGain()
{
    // LOG_INFO("WINDOW FOCUS GAIN");
}

void Engine::EventJoystickConnected(const int id)
{
    LOG_INFO("JOYSTICK WITH ID : {} CONNECTED ", id);
}

void Engine::EventJoystickDisconnected(const int id)
{
    LOG_INFO("JOYSTICK WITH ID : {} DISCONNECTED ", id);
}

void Engine::EventMouseButtonPressed()
{
    LOG_INFO("MOUSE BUTTON PRESSED");
}

void Engine::EventWindowScreenshot() {
    m_engineContext.screenshot.Take();
}
