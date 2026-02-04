#pragma once

#include <SFML/Graphics.hpp>

#include "Core/EngineContext.h"
#include "Core/EngineVisitor.h"
#include "Core/Overlay.h"

#include "Scene/Scene.h"
#include "Scene/SceneFactory.h"

class Engine {
  public:
    Engine();

    bool IsRunning() const;

    void ProcessEvents();
    void Update();
    void Render();

  private:
    sf::RenderWindow m_window;
    EngineContext m_engineContext;

    SceneFactory::Scenes m_scenes;
    Scene *m_currentScene{nullptr};

    Overlay m_overlay;
    bool m_cursorWasVisible;

private:
    friend EngineVisitor;

    void EventWindowClose();
    void EventWindowResize(const sf::Vector2u& windowSize);
    void EventWindowFocusLost();
    void EventWindowFocusGain();
    void EventJoystickConnected(const int id);
    void EventJoystickDisconnected(const int id);
    void EventMouseButtonPressed();
    void EventWindowScreenshot();
    void EventSceneChange(const std::string &sceneName);
    void EventSceneRestart();
    void EventSceneMenuReturn();
    void EventOverlayPauseToggle();
    void EventOverlaySelection(OverlaySelection selection);
};
