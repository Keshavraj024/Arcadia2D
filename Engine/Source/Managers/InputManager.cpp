#include "Managers/InputManager.h"
#include "Utils/Log.h"

#include <algorithm>

void InputManager::Bind(int actionId, const Input::Binding &binding) {
  m_bindings.emplace(actionId, binding);
}

bool InputManager::Pressed(int actionId) {
  auto [first, last] = m_bindings.equal_range(actionId);

  return std::any_of(first, last, [this](const auto &entry) {
    return std::visit([this](const auto &binding) { return this->Pressed(binding); }, entry.second);
  });
}

void InputManager::Clear()
{
    m_bindings.clear();
}

bool InputManager::Pressed(const Input::Keyboard &keyboard) const {
    return sf::Keyboard::isKeyPressed(keyboard.key);
}

bool InputManager::Pressed(const Input::Mouse &mouse) const {
  return sf::Mouse::isButtonPressed(mouse.button);
}

bool InputManager::Pressed(const Input::Gamepad &gamePad) const {
  const auto button = Input::LogicalToHardware(gamePad.button, gamePad.id);
  return button ? sf::Joystick::isButtonPressed(gamePad.id, *button) : false;
}

bool InputManager::Pressed(const Input::Axis &binding) const {
  const float axis =
      sf::Joystick::getAxisPosition(binding.id, binding.axis) / 100;  // clamp between - 1 and 1
  return (binding.threshold >= 0) ? (axis > binding.threshold) : (axis < binding.threshold);
}
