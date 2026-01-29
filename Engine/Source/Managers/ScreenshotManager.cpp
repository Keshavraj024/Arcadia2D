
#include <chrono>
#include <string>
#include <format>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <filesystem>

#include "Managers/ScreenshotManager.h"
#include "Utils/Log.h"


ScreenshotManager::ScreenshotManager(const sf::RenderWindow &window): m_window(window) {}

void ScreenshotManager::Take() {

    std::string filename = std::format("Screenshot_{:%Y%m%d_%H%M%S}",
                                       floor<std::chrono::milliseconds>(std::chrono::system_clock::now()));

    filename.replace(filename.find("."), 1, "_");

    sf::Texture screenshot(m_window.getSize());
    screenshot.update(m_window);

    std::filesystem::create_directories("Content/Screenshots");

    if(screenshot.copyToImage().saveToFile("Content/Screenshots/"+filename+".png")) {
        LOG_INFO("Screenshot saved to {}", filename);
    } else {
        LOG_ERROR("Failed to save screenshot {}", "Content/Screenshots/"+filename);
    }
}
