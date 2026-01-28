#pragma once

#include <unordered_map>

#include "Utils/InputBindings.h"

class InputManager {
  public:
    void Bind(int actionId, const Input::Binding& binding);
    bool Pressed(int actionId);

  private:
    std::unordered_multimap<int, Input::Binding> m_bindings;

  private:
    bool Pressed(const Input::Keyboard&) const;
    bool Pressed(const Input::Mouse&) const;
    bool Pressed(const Input::Gamepad&) const;
    bool Pressed(const Input::Axis&) const;
};
