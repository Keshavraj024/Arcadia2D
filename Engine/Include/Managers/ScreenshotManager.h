#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class ScreenshotManager {
  public:
    ScreenshotManager(const sf::RenderWindow &window);
    void Take();

  private:
    const sf::RenderWindow &m_window;
};
