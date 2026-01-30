#include "Core/EngineConfig.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <cassert>

EngineConfig::EngineConfig() {

  std::ifstream file("Content/Config.json");
  assert(file);

  nlohmann::json json = nlohmann::json::parse(file);

  windowSize = {json["windowSize"][0], json["windowSize"][1]};
  windowTitle = json["windowTitle"];
  disableSfmlLogs = json["disableSfmlLogs"];
  maxDeltaTime = sf::seconds(json["maxDeltaTime"]);
  globalVolume = json["globalVolume"];
  backgroundColor = {json["backgroundColor"][0],
                     json["backgroundColor"][1],
                     json["backgroundColor"][2]};

  cursorSpeed = json["cursorSpeed"];
  cursorRadius = json["cursorRadius"];
  cursorColor = {json["cursorColor"][0], json["cursorColor"][1], json["cursorColor"][2]};
  joystickDeadzone = json["joystickDeadzone"];
  cursorVisibility = json["cursorVisibility"];

  guiTheme = (json["Gui"]["theme"]).get<std::string>();
  guiFont = json["Gui"]["font"];


}
