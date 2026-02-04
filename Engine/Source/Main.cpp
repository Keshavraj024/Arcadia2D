#include "Core/Engine.h"
#include <SFML/GpuPreference.hpp>
#include <SFML/System/Sleep.hpp>

SFML_DEFINE_DISCRETE_GPU_PREFERENCE

int main() {

  Engine engine;

  while(engine.IsRunning()) {
    engine.ProcessEvents();

    if (!engine.HasFocus()) {
        sf::sleep(sf::milliseconds(10));
        continue;
    }

    engine.Update();
    engine.Render();
  }


  return 0;

}
