#pragma once

#include <SFML/Graphics.hpp>

class RenderManager
{
public:
    RenderManager();

    void Draw(const sf::Drawable &drawable);

    // For cameras later
    void SetView(const sf::View &view);
    void ResetView();

private:
    sf::RenderTexture m_renderTexture;
    sf::RectangleShape m_backgroundShape;
    sf::Texture m_backgroundTexture;

private:
    friend class Engine;
    // Engine uses these function to draw every frame
    void BeginDrawing();
    const sf::Texture &FinishDrawing();
};
