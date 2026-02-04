#pragma once

#include "Graphics/Effects.h"

#include <SFML/Graphics/Shader.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

class EffectGlitch : public Effects
{
public:
    EffectGlitch();
    ~EffectGlitch();

    void Apply(const sf::Texture &input, sf::RenderTarget &target) override;

private:
    sf::Shader m_glitchShader;
    sf::Clock m_clock;
};
