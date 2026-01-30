#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <optional>
#include <ranges>
#include <vector>

#include "Core/EngineConfig.h"
#include "Utils/Cooldown.h"
#include "Utils/Log.h"
#include "Utils/Verify.h"

inline const sf::Font &GetDefaultFont()
{
    static const sf::Font font("Content/Fonts/PressStart2P-Regular.ttf");
    return font;
}

inline bool IsShapeOutsideWindowLeft(const sf::Shape &shape)
{
    return shape.getPosition().x < shape.getGlobalBounds().size.x / 2;
}

inline bool IsShapeOutsideWindowRight(const sf::Shape &shape)
{
    return shape.getPosition().x
           > (gEngineConfig.windowSize.x - shape.getGlobalBounds().size.x / 2);
}

inline bool IsShapeOutsideWindowTop(const sf::Shape &shape)
{
    return shape.getPosition().y < shape.getGlobalBounds().size.y / 2;
}

inline bool IsShapeOutsideWindowBottom(const sf::Shape &shape)
{
    return shape.getPosition().y
           > (gEngineConfig.windowSize.y - shape.getGlobalBounds().size.y / 2);
}

inline bool IsPointWithinWindow(const sf::Vector2f &point)
{
    return point.x < 0 || point.x >= gEngineConfig.windowSize.x || point.y < 0
           || point.y >= gEngineConfig.windowSize.y;
}

inline std::optional<sf::FloatRect> IsShapeIntersects(const sf::Shape &shape1,
                                                      const sf::Shape &shape2)
{
    return shape1.getGlobalBounds().findIntersection(shape2.getGlobalBounds());
}

inline float DistanceSquared(const sf::Vector2f &point1, const sf::Vector2f &point2)
{
    return (point1 - point2).lengthSquared();
}

inline float Distance(const sf::Vector2f &point1, const sf::Vector2f &point2)
{
    return (point1 - point2).length();
}

inline bool Contains(const sf::Shape &shape, const sf::Vector2f &point)
{
    return shape.getGlobalBounds().contains(point);
}

inline bool Contains(const sf::CircleShape &shape, const sf::Vector2f &point)
{
    return DistanceSquared(shape.getPosition(), point) <= std::pow(shape.getRadius(), 2);
}

inline sf::Vector2f Lerp(const sf::Vector2f &start, const sf::Vector2f &end, float t)
{
    return {std::lerf(start.x, end.x, t), std::lerf(start.y, end.y, t)};
}
