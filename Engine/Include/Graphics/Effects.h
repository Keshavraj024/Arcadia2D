#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

class Effects
{
public:
    virtual ~Effects() = default;

    virtual void Apply(const sf::Texture &input, sf::RenderTarget &target) = 0;
};
