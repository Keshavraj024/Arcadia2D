#pragma once

#include "Types/BounceTypes.h"

namespace Bounce {
class Game : public Scene
{
public:
    Game(EngineContext &context);
    ~Game();

    void Start() override;
    void Update() override;
    void Render() override;
    void OnPause(bool paused) override;
    void OnCleanup() override;

private:
    Bounce::Paddle m_paddle;
    std::vector<Bounce::Ball> m_balls;
    Bounce::GameStats m_stats;
    sf::Sound m_sound;
    sf::Music m_music;
    Cooldown m_ballSpawnCooldown;
    sf::RectangleShape m_background;

private:
    void InitPaddle();
    void InitStats();
    void InitBackground();
    void InitSound();
    void InitMusic();

    void BindInputs();

    void StartPaddle();
    void StartStats();
    void StartMusic();

    void UpdatePaddle();
    void UpdateBalls();
    void UpdateBall(Ball &ball);

    void EventBallSpawn();
    void EventBallMissed(int ballsMissed);

    void HandleCollisions();
    void HandleCollisionsPaddleBall();
    void ResolveCollisionPaddleBall(Bounce::Ball &ball);
    void HandleCollisionsMap();
};
} // namespace Bounce
