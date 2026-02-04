#include "Graphics/Effects/EffectGlitch.h"
#include "SFML/Graphics/Sprite.hpp"
#include "Utils/Verify.h"

EffectGlitch::EffectGlitch()
{
    VERIFY(m_glitchShader.loadFromFile("Content/Shaders/Glitch.frag", sf::Shader::Type::Fragment));
}

EffectGlitch::~EffectGlitch() {}

void EffectGlitch::Apply(const sf::Texture &input, sf::RenderTarget &target)
{
    m_glitchShader.setUniform("sourceTexture", sf::Shader::CurrentTexture);
    m_glitchShader.setUniform("time", m_clock.getElapsedTime().asSeconds());

    target.draw(sf::Sprite(input), &m_glitchShader);
}
