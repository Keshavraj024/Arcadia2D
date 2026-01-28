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
}
