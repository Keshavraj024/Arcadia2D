#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>

class GuiManager
{
public:
    GuiManager(sf::RenderWindow& window);
    ~GuiManager();

    void AddWidget(const tgui::Widget::Ptr& widget);
    void RemoveWidget(const tgui::Widget::Ptr& widget);

private:
    sf::RenderWindow& m_renderWindow;
    tgui::Gui m_tgui;

private:
    friend class Engine;
    void ProcessEvent(const sf::Event&);
    void Render();

private:
    void HandleEvent(const sf::Event::Resized&);
    void HandleEvent(const sf::Event::JoystickButtonPressed&);
    void HandleEvent(const sf::Event::JoystickButtonReleased&);
    void HandleEvent(const auto&) {};

};

