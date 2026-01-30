#pragma once

#include <optional>
#include <string>
#include <string_view>

class SceneManager
{
public:
    SceneManager();
    ~SceneManager();

    void ChangeScene(std::string_view scene);
    void RestartScene();

private:
    std::string m_currentScene;
    std::optional<std::string> m_nextScene;

private:
    friend class Engine;
    std::optional<std::string> FetchScene();
};
