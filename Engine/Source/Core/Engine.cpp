#include "Core/Engine.h"
#include "Core/EngineConfig.h"
#include "Utils/Log.h"

Engine::Engine() : m_window(sf::VideoMode(sf::Vector2u{gEngineConfig.windowSize}), gEngineConfig.windowTitle), m_engineContext(m_window)
{
  m_window.setIcon(sf::Image("Content/Textures/windowIcon.png"));
  m_window.setMinimumSize(m_window.getSize() / 2u);
  m_window.setMouseCursorVisible(false);

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
    if(const auto nextScene = m_engineContext.scenes.FetchScene()) {
        EventSceneChange(nextScene.value());
    }

  while(const auto event = m_window.pollEvent()) {
        if(event.has_value()) {
          event->visit(EngineVisitor{*this});
          m_engineContext.gui.ProcessEvent(event.value());
        }
  }
}

void Engine::Update()
{
  m_engineContext.time.Update();
  m_engineContext.cursor.Update(m_engineContext.time.GetDeltaTime());
}

void Engine::Render()
{
  m_window.clear();

  m_engineContext.renderer.BeginDrawing();

  m_window.draw(sf::Sprite(m_engineContext.renderer.FinishDrawing()));

  m_engineContext.gui.Render();

  m_engineContext.cursor.Render();

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

void Engine::EventSceneChange([[maybe_unused]] std::string_view sceneName) {
    // TODO IMPLEMENT LATER
}

void Engine::EventSceneRestart() {
    m_engineContext.scenes.RestartScene();
}

void Engine::EventSceneMenuReturn() {
    m_engineContext.scenes.ChangeScene("Menu");
}
