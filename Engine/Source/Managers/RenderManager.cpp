#include "Managers/RenderManager.h"
#include "Core/EngineConfig.h"

RenderManager::RenderManager()
    : m_renderTexture(sf::Vector2u(gEngineConfig.windowSize))
    , m_backgroundShape(gEngineConfig.windowSize)
    , m_backgroundTexture("Content/Textures/backgroundImage.png")
{
    m_renderTexture.setSmooth(true);
    m_backgroundShape.setTexture(&m_backgroundTexture);
    m_backgroundShape.setFillColor(gEngineConfig.backgroundColor);
}

void RenderManager::Draw(const sf::Drawable &drawable)
{
    m_renderTexture.draw(drawable);
}

void RenderManager::SetView(const sf::View &view)
{
    m_renderTexture.setView(view);
}

void RenderManager::ResetView()
{
    m_renderTexture.setView(m_renderTexture.getDefaultView());
}

void RenderManager::BeginDrawing()
{
    m_renderTexture.clear();

    Draw(m_backgroundShape);
}

const sf::Texture &RenderManager::FinishDrawing()
{
    m_renderTexture.display();

    return m_renderTexture.getTexture();
}
