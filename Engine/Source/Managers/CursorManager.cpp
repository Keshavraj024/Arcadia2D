#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Mouse.hpp>
#include <algorithm>

#include "Core/EngineConfig.h"
#include "Managers/CursorManager.h"

CursorManager::CursorManager(sf::RenderWindow &window)
    : m_renderWindow(window)
    , m_cursorSpeed{gEngineConfig.cursorSpeed}
    , m_isCursorVisible(gEngineConfig.cursorVisibility)
{
    m_circleShape.setRadius(gEngineConfig.cursorRadius);
    m_circleShape.setFillColor(gEngineConfig.cursorColor);
    m_circleShape.setOrigin(m_circleShape.getGeometricCenter());
    m_circleShape.setPosition(gEngineConfig.windowSize / 2.f);

    m_cursorPos = GetPosition();
}

CursorManager::~CursorManager() {}

void CursorManager::Update(const float deltaTime)
{
    sf::Vector2f joystickDir(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) / 100,
                             sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) / 100);

    if (joystickDir.length() > gEngineConfig.joystickDeadzone) {
        m_cursorPos += joystickDir * m_cursorSpeed * deltaTime;

        m_cursorPos.x = std::clamp(m_cursorPos.x, 0.f, gEngineConfig.windowSize.x);
        m_cursorPos.y = std::clamp(m_cursorPos.y, 0.f, gEngineConfig.windowSize.y);

        m_circleShape.setPosition(m_cursorPos);
        SetPosition(m_cursorPos);
    } else {
        m_circleShape.setPosition(GetPosition());
    }
}

void CursorManager::Render() const
{
    if (gEngineConfig.cursorVisibility) {
        m_renderWindow.draw(m_circleShape);
    }
}

float CursorManager::cursorSpeed() const
{
    return m_cursorSpeed;
}

void CursorManager::setCursorSpeed(float newCursorSpeed)
{
    m_cursorSpeed = newCursorSpeed;
}

bool CursorManager::isCursorVisible() const
{
    return m_isCursorVisible;
}

void CursorManager::setIsCursorVisible(bool newIsCursorVisible)
{
    m_isCursorVisible = newIsCursorVisible;
}

void CursorManager::SetPosition(sf::Vector2f position)
{
    sf::Mouse::setPosition(m_renderWindow.mapCoordsToPixel(position,
                                                           m_renderWindow.getDefaultView()),
                           m_renderWindow);
}

sf::Vector2f CursorManager::GetPosition() const
{
    return GetPosition(m_renderWindow.getDefaultView());
}

sf::Vector2f CursorManager::GetPosition(const sf::View &view) const
{
    return m_renderWindow.mapPixelToCoords(sf::Mouse::getPosition(m_renderWindow), view);
}
