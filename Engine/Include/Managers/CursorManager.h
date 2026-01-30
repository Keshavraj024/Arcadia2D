#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

class CursorManager{
public:
    CursorManager(sf::RenderWindow &window);

    ~CursorManager();

    float cursorSpeed() const;
    void setCursorSpeed(float newCursorSpeed);

    bool isCursorVisible() const;
    void setIsCursorVisible(bool newIsCursorVisible);

    void SetPosition(sf::Vector2f position);
    sf::Vector2f GetPosition() const;
    sf::Vector2f GetPosition(const sf::View &view) const;

private:
    sf::RenderWindow &m_renderWindow;
    sf::CircleShape m_Shape;
    float m_cursorSpeed;
    bool m_isCursorVisible;

    sf::Vector2f m_cursorPos;

private:
    friend class Engine;
    void Update(const float deltaTime);
    void Render() const;
};
