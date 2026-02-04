#include "Core/Engine.h"
#include "Core/EngineConfig.h"
#include "Utils/Log.h"

Engine::Engine()
    : m_window(sf::VideoMode(sf::Vector2u{gEngineConfig.windowSize}), gEngineConfig.windowTitle)
    , m_engineContext(m_window)
    , m_scenes(SceneFactory::CreateScenes(m_engineContext))
    , m_overlay(m_engineContext.gui)
    , m_cursorWasVisible{false}
{
  m_window.setIcon(sf::Image("Content/Textures/windowIcon.png"));
  m_window.setMinimumSize(m_window.getSize() / 2u);
  m_window.setMouseCursorVisible(false);

  if(gEngineConfig.disableSfmlLogs) {
    sf::err().rdbuf(nullptr);
  }


  LOG_INFO("WINDOW IS CREATED");

  m_engineContext.audio.SetGlobalVolume(gEngineConfig.globalVolume);
  m_engineContext.scenes.ChangeScene("Bounce");
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

          if (!m_overlay.IsVisible() && m_currentScene)
              m_currentScene->OnEvent(event.value());

          if (const auto selection = m_overlay.FetchSelection()) {
              EventOverlaySelection(selection.value());
          }
        }
  }
}

void Engine::Update()
{
  m_engineContext.time.Update();
  m_engineContext.cursor.Update(m_engineContext.time.GetDeltaTime());

  if (!m_overlay.IsVisible() && m_currentScene)
      m_currentScene->Update();
}

void Engine::Render()
{
  m_window.clear();

  m_engineContext.renderer.BeginDrawing();

  if (m_currentScene)
      m_currentScene->Render();

  m_window.draw(sf::Sprite(m_engineContext.renderer.FinishDrawing()));

  m_engineContext.gui.Render();

  m_engineContext.cursor.Render();

  m_window.display();
}

bool Engine::HasFocus()
{
    return m_window.hasFocus();
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
    if (m_currentScene)
        m_currentScene->OnPause(true);
    // LOG_INFO("WINDOW FOCUS LOST");
}

void Engine::EventWindowFocusGain()
{
    if (m_currentScene)
        m_currentScene->OnPause(m_overlay.IsVisible());
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

void Engine::EventSceneChange(const std::string &sceneName)
{
    assert(m_scenes.contains(sceneName));
    Scene *nextScene = m_scenes.at(sceneName).get();

    if (m_currentScene)
        m_currentScene->OnCleanup();

    m_engineContext.input.Clear();
    m_currentScene = nextScene;
    m_currentScene->Start();
}

void Engine::EventSceneRestart() {
    m_overlay.SetVisible(false);
    m_engineContext.scenes.RestartScene();
}

void Engine::EventSceneMenuReturn() {
    m_overlay.SetVisible(false);
    m_engineContext.scenes.ChangeScene("Menu");

    m_engineContext.cursor.setIsCursorVisible(true);
    m_engineContext.cursor.setCursorSpeed(gEngineConfig.cursorSpeed);
}

void Engine::EventOverlayPauseToggle()
{
    const auto isOverlayVisible = !m_overlay.IsVisible();
    m_overlay.SetVisible(isOverlayVisible);

    auto cursorVisibility = m_engineContext.cursor.isCursorVisible();
    m_engineContext.cursor.setIsCursorVisible(isOverlayVisible || m_cursorWasVisible);
    m_cursorWasVisible = cursorVisibility;

    if (m_currentScene)
        m_currentScene->OnPause(isOverlayVisible);

    LOG_INFO(isOverlayVisible ? "Game Paused " : "Game Resumed");
}

void Engine::EventOverlaySelection(OverlaySelection selection)
{
    switch (selection) {
    case OverlaySelection::Resume:
        EventOverlayPauseToggle();
        break;
    case OverlaySelection::Restart:
        EventSceneRestart();
        break;
    case OverlaySelection::Menu:
        EventSceneMenuReturn();
        break;
    case OverlaySelection::Quit:
        EventWindowClose();
        break;
    default:
        break;
    }
}
