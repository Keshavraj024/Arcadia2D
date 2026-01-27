#pragma once

#include <SFML/Graphics.hpp>
#include "Core/EngineVisitor.h"

class Engine {
  public:
    Engine();

    bool IsRunning() const;

    void ProcessEvents();
    void Update();
    void Render();

  private:
    sf::RenderWindow m_window;

  private:
    friend EngineVisitor;
    void  EngineWindowClose();
    void EngineWindowResize(const sf::Vector2u& windowSize);
    void EngineWindowFocusLost();
    void EngineWindowFocusGain();
};
