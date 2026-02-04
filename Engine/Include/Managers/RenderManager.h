#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

// #include "Graphics/Effects.h"

class Effects;

class RenderManager
{
public:
    RenderManager();
    ~RenderManager();

    void Draw(const sf::Drawable &drawable);

    // For cameras later
    void SetView(const sf::View &view);
    void ResetView();

private:
    sf::RenderTexture m_renderTexture;
    sf::RectangleShape m_backgroundShape;
    sf::Texture m_backgroundTexture;

    sf::RenderTexture m_effectsTarget;
    std::vector<std::unique_ptr<Effects>> m_effects;

private:
    friend class Engine;
    // Engine uses these function to draw every frame
    void BeginDrawing();
    const sf::Texture &FinishDrawing();
};
