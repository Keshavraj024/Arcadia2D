#include "Scene/SceneFactory.h"
#include "Bounce.h"

namespace SceneFactory {
Scenes CreateScenes(EngineContext &engineContext)
{
    Scenes scenes;

    scenes["Bounce"] = std::make_unique<Bounce::Game>(engineContext);

    return scenes;
}
} // namespace SceneFactory
