#pragma once

#include <string_view>
#include "nlohmann/json.hpp"

class SaveManager {
  public:
    SaveManager();
    ~SaveManager();

    void Set(std::string_view key, auto value) {
      m_values[key] = value;
    }

    auto Get(std::string_view key, auto defaultValue = {}) const {
      return m_values.value(key, defaultValue);
    }

    bool Has(std::string_view key);
    void Erase(std::string_view key);
    void Clear();

  private:
    nlohmann::json m_values;

};
