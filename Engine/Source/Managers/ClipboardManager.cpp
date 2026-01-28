#include "Managers/ClipboardManager.h"
#include <SFML/Window/Clipboard.hpp>

void ClipboardManager::SetString(const sf::String& string)
{
  sf::Clipboard::setString(string);
}

sf::String ClipboardManager::GetString() const noexcept
{
  return sf::Clipboard::getString();
}
