#include "Graphics/Effects/EffectInverted.h"
#include "SFML/Graphics/Sprite.hpp"
#include "Utils/Verify.h"

EffectInverted::EffectInverted()
{
    VERIFY(m_invertedShader.loadFromFile("Content/Shaders/Invert.frag", sf::Shader::Type::Fragment));
}

void EffectInverted::Apply(const sf::Texture &input, sf::RenderTarget &target)
{
    m_invertedShader.setUniform("sourceTexture", sf::Shader::CurrentTexture);
    target.draw(sf::Sprite(input), &m_invertedShader);
}
