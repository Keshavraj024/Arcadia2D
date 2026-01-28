#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>

#include <string>
#include <unordered_map>
#include <optional>

class ResourceManager {
  public:
    sf::Texture* FetchTexture(const std::string& filename);
    sf::SoundBuffer* FetchSoundBuffer(const std::string& filename) ;
    sf::Font* FetchFont(const std::string& filename) ;
    std::optional<sf::Music> FetchMusic(const std::string& filename);


  private:
    std::unordered_map<std::string, sf::Texture> m_textures;
    std::unordered_map<std::string, sf::Font> m_fonts;
    std::unordered_map<std::string, sf::SoundBuffer> m_soundBuffer;

};
