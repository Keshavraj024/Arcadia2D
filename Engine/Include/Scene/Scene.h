#pragma once

#include <SFML/Window/Event.hpp>

#include "Core/EngineContext.h"

class Scene
{
public:
    Scene(EngineContext &ctx)
        : ctx(ctx) {};
    virtual ~Scene() = default;

    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;

    virtual void OnEvent(const sf::Event &) {}
    virtual void OnPause(bool /*paused*/) {}
    virtual void OnCleanup() {}

protected:
    EngineContext &ctx;

private:
};
