#include "Managers/ResourceManager.h"
#include "Utils/Log.h"


sf::Texture *ResourceManager::FetchTexture(const std::string &filename)
{
  if(!m_textures.contains(filename)) {
    if(!m_textures[filename].loadFromFile("Content/Textures/"+ filename)) {
      LOG_ERROR("Texture file is not found {}", filename);
      return nullptr;
    }
  }
  return &m_textures.at(filename);
}

sf::SoundBuffer *ResourceManager::FetchSoundBuffer(const std::string &filename)
{
  if(!m_soundBuffer.contains(filename)) {
    if(!m_soundBuffer[filename].loadFromFile("Content/SoundBuffers/"+ filename)) {
      LOG_ERROR("SoundBuffer file is not found {}", filename);
      return nullptr;
    }
  }
  return &m_soundBuffer.at(filename);
}

sf::Font *ResourceManager::FetchFont(const std::string &filename)
{
  if(!m_fonts.contains(filename)) {
    if(!m_fonts[filename].openFromFile("Content/Fonts/"+ filename)) {
      LOG_ERROR("Font file is not found {}", filename);
      return nullptr;
    }
  }
  return &m_fonts.at(filename);
}

std::optional<sf::Music> ResourceManager::FetchMusic(const std::string &filename)
{
  sf::Music music;

  if(!music.openFromFile("Content/Musics/"+ filename)) {
    LOG_ERROR("Music file is not found {}", filename);
    return std::nullopt;
  }

  return music;
}
