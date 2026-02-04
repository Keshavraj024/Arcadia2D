#include "Managers/RenderManager.h"
#include "Core/EngineConfig.h"
#include "Graphics/Effects/EffectGlitch.h"
#include "Graphics/Effects/EffectInverted.h"
#include "Utils/Verify.h"

#include <utility>

RenderManager::RenderManager()
    : m_renderTexture(sf::Vector2u(gEngineConfig.windowSize))
    , m_backgroundShape(gEngineConfig.windowSize)
    , m_backgroundTexture("Content/Textures/backgroundImage.png")
{
    m_renderTexture.setSmooth(true);
    m_backgroundShape.setTexture(&m_backgroundTexture);
    m_backgroundShape.setFillColor(gEngineConfig.backgroundColor);

    if (sf::Shader::isAvailable()) {
        VERIFY(m_effectsTarget.resize(sf::Vector2u(gEngineConfig.windowSize)));

        m_effects.emplace_back(std::make_unique<EffectInverted>());
        m_effects.emplace_back(std::make_unique<EffectGlitch>());
    }
}

RenderManager::~RenderManager() {}

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

    sf::RenderTexture *input = &m_renderTexture;
    sf::RenderTexture *output = &m_effectsTarget;

    std::ranges::for_each(m_effects, [&](auto &effect) {
        output->clear();
        effect->Apply(input->getTexture(), *output);
        output->display();

        std::swap(input, output);
    });

    // for(auto& effect: m_effects) {
    //     output->clear();
    //     effect->Apply(input->getTexture(), *output);
    //     output->display();

    //     std::swap(input, output);
    // }

    return m_renderTexture.getTexture();
}
