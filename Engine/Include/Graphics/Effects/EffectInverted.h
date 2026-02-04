#pragma once

#include "Graphics/Effects.h"
#include <SFML/Graphics/Shader.hpp>

class EffectInverted : public Effects
{
public:
    EffectInverted();
    void Apply(const sf::Texture &input, sf::RenderTarget &target) override;

private:
    sf::Shader m_invertedShader;
};
