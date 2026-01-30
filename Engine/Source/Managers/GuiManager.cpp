#include "Managers/GuiManager.h"

#include "Core/EngineConfig.h"
#include "Utils/InputBindings.h"

GuiManager::GuiManager(sf::RenderWindow &window): m_renderWindow(window), m_tgui{m_renderWindow} {
    m_tgui.setTabKeyUsageEnabled(true);

    tgui::Font font{gEngineConfig.guiFont};
    m_tgui.setFont(font);
    tgui::Theme::setDefault(gEngineConfig.guiTheme);
}

GuiManager::~GuiManager() {}

void GuiManager::AddWidget(const tgui::Widget::Ptr &widget) {
    m_tgui.add(widget);
}

void GuiManager::RemoveWidget(const tgui::Widget::Ptr &widget) {
    m_tgui.remove(widget);
}

void GuiManager::ProcessEvent(const sf::Event &event) {
    event.visit([this](const auto& type) {
        this->HandleEvent(type);
        m_tgui.handleEvent(type);
    });
}

void GuiManager::Render() {
    m_tgui.draw();
}

void GuiManager::HandleEvent(const sf::Event::Resized &resized) {
    const auto defaultSize = m_renderWindow.getDefaultView().getSize();
    const auto scale = sf::Vector2f(resized.size).componentWiseDiv(defaultSize);
    m_tgui.setRelativeView({0, 0, 1 / scale.x, 1 / scale.y});
}

void GuiManager::HandleEvent(const sf::Event::JoystickButtonPressed &joystick) {

    if(Input::HardwareToLogical(joystick.button, joystick.joystickId) == GamepadButton::South) {
        m_tgui.handleEvent(sf::Event::MouseButtonPressed{{}, sf::Mouse::getPosition(m_renderWindow)});
    }
}

void GuiManager::HandleEvent(const sf::Event::JoystickButtonReleased &joystick) {
    if(Input::HardwareToLogical(joystick.button, joystick.joystickId) == GamepadButton::South) {
        m_tgui.handleEvent(sf::Event::MouseButtonReleased{{}, sf::Mouse::getPosition(m_renderWindow)});
    }
}
