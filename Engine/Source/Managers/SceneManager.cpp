#include "Managers/SceneManager.h"
#include "Utils/Log.h"

SceneManager::SceneManager() {}

SceneManager::~SceneManager() {}

void SceneManager::ChangeScene(std::string_view scene) {
    if(!m_nextScene.has_value()) {
        m_nextScene = scene;
    }
}

void SceneManager::RestartScene() {
    ChangeScene(m_currentScene);
}

std::optional<std::string> SceneManager::FetchScene() {
    if(m_nextScene.has_value()) {
        if(m_currentScene == m_nextScene.value()) {
            LOG_INFO("Restarting scene : {}", m_currentScene);
        }
        else {
            LOG_INFO("Changing scene to: {}", m_nextScene.value());
        }
        m_currentScene = m_nextScene.value();
        return std::exchange(m_nextScene, std::nullopt);
    }


    return std::nullopt;
}
