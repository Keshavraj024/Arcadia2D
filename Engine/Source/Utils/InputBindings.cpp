#include "Utils/InputBindings.h"

#include <array>

namespace mapping {
  const std::array<int, 12> Playstation{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  const std::array<int, 12> xBox{2, 0, 1, 3, 4, 5, -1, -1, 6, 7, 8, 9};

  const int MicrosoftVID = 0x045E;

  const auto& GetMapping(int id) {
    const int vendorId = sf::Joystick::getIdentification(id).vendorId;
    return (vendorId == MicrosoftVID) ? xBox : Playstation;
  }

}  // namespace mapping

std::optional<int> Input::LogicalToHardware(GamepadButton button, int id) {
  const auto mapping = mapping::GetMapping(id);
  const auto value = mapping[static_cast<int>(button)];
  return (value != -1) ? std::optional<int>(value) : std::nullopt;
}

std::optional<GamepadButton> Input::HardwareToLogical(int button, int id) {
  const auto mapping = mapping::GetMapping(id);

  if (const auto value = std::ranges::find(mapping, button); value != mapping.end()) {
    auto index = std::distance(mapping.begin(), value);
    return GamepadButton{index};
  }

  return std::nullopt;
}
