#include "Bounce.h"

using namespace Bounce;

Game::Game(EngineContext &context)
    : Scene(context)
    , m_sound(*ctx.resource.FetchSoundBuffer(BOUNCE_SOUND_FILENAME))
    , m_music(*ctx.resource.FetchMusic(MUSIC_FILENAME))
    , m_ballSpawnCooldown(BALL_SPAWN_COOLDOWN_DURATION)
{
    InitPaddle();
    InitStats();
    InitBackground();
    InitSound();
    InitMusic();
}

Game::~Game() {}

void Game::Start()
{
    ctx.cursor.setIsCursorVisible(false);

    BindInputs();

    m_balls.clear();

    StartPaddle();
    StartStats();
    StartMusic();

    m_ballSpawnCooldown.Restart();
}

void Game::Update()
{
    if (m_ballSpawnCooldown.IsOver()) {
        EventBallSpawn();
        m_ballSpawnCooldown.Restart();
    }

    UpdatePaddle();
    UpdateBalls();

    HandleCollisions();
}

void Game::Render()
{
    ctx.renderer.Draw(m_background);
    ctx.renderer.Draw(m_paddle.shape);

    std::ranges::for_each(m_balls, [this](auto &ball) { ctx.renderer.Draw(ball.shape); });

    ctx.renderer.Draw(m_stats.scoreText);
    ctx.renderer.Draw(m_stats.highScoreText);
    ctx.renderer.Draw(m_stats.livesText);
}

void Game::OnPause(bool paused)
{
    if (paused) {
        m_sound.stop();
        m_music.pause();
        m_ballSpawnCooldown.Stop();
    } else {
        m_music.play();
        m_ballSpawnCooldown.Restart();
    }
}

void Game::OnCleanup()
{
    m_music.stop();
    m_sound.stop();
}

void Game::InitPaddle()
{
    m_paddle.shape.setFillColor(PADDLE_COLOR);
    m_paddle.shape.setSize(PADDLE_SIZE);

    m_paddle.shape.setOrigin(m_paddle.shape.getGeometricCenter());

    m_paddle.speed = PADDLE_SPEED;
}

void Game::InitStats()
{
    m_stats.scoreText.setFillColor(STATS_SCORE_TEXT_COLOR);
    m_stats.scoreText.setPosition({10, 10});

    m_stats.highScoreText.setFillColor(STATS_HIGH_SCORE_TEXT_COLOR);
    m_stats.highScoreText.setPosition({10, 60});

    m_stats.livesText.setFillColor(STATS_LIVES_TEXT_COLOR);
    m_stats.livesText.setPosition({10, 110});
}

void Game::InitBackground()
{
    m_background.setTexture(ctx.resource.FetchTexture(BACKGROUND_TEXTURE_FILENAME));
    m_background.setSize(gEngineConfig.windowSize);
}

void Game::InitSound()
{
    m_sound.setVolume(BOUNCE_SOUND_VOLUME);
}

void Game::InitMusic()
{
    m_music.setVolume(MUSIC_VOLUME);
    m_music.setPitch(MUSIC_PITCH);
    m_music.setLooping(true);
}

void Game::BindInputs()
{
    ctx.input.Bind(Action::MOVELEFT, Input::Keyboard{.key = sf::Keyboard::Scan::Left});
    ctx.input.Bind(Action::MOVELEFT,
                   Input::Axis{.axis = sf::Joystick::Axis::X, .threshold = -0.25f});

    ctx.input.Bind(Action::MOVERIGHT, Input::Keyboard{.key = sf::Keyboard::Scan::Right});
    ctx.input.Bind(Action::MOVERIGHT,
                   Input::Axis{.axis = sf::Joystick::Axis::X, .threshold = 0.25f});
}

void Game::StartPaddle()
{
    m_paddle.shape.setPosition(gEngineConfig.windowSize.componentWiseMul({0.50f, 0.90f}));
}

void Game::StartStats()
{
    m_stats.score = 0;
    m_stats.scoreText.setString("Score : " + std::to_string(m_stats.score));

    m_stats.highScore = ctx.save.Get<int>(STATS_HIGH_SCORE_KEY);
    m_stats.highScoreText.setString("High Score : " + std::to_string(m_stats.highScore));

    m_stats.lives = PADDLE_LIVES;
    m_stats.livesText.setString("Lives : " + std::to_string(m_stats.lives));
}

void Game::StartMusic()
{
    m_music.play();
}

void Game::UpdatePaddle()
{
    auto lastPosition = m_paddle.shape.getPosition();

    if (ctx.input.Pressed(Action::MOVELEFT)) {
        m_paddle.shape.move({-m_paddle.speed * ctx.time.GetDeltaTime(), 0});
    }

    if (ctx.input.Pressed(Action::MOVERIGHT)) {
        m_paddle.shape.move({m_paddle.speed * ctx.time.GetDeltaTime(), 0});
    }

    if (IsShapeOutsideWindowLeft(m_paddle.shape) || IsShapeOutsideWindowRight(m_paddle.shape))
        m_paddle.shape.setPosition(lastPosition);
}

void Game::UpdateBalls()
{
    for (auto &ball : m_balls) {
        UpdateBall(ball);
    }
}

void Game::UpdateBall(Ball &ball)
{
    auto lastPosition = ball.shape.getPosition();

    ball.shape.move(ball.direction * ball.speed * ctx.time.GetDeltaTime());

    if (IsShapeOutsideWindowLeft(ball.shape) || IsShapeOutsideWindowRight(ball.shape)) {
        ball.shape.setPosition(lastPosition);
        ball.direction.x *= -1;
    }

    if (IsShapeOutsideWindowTop(ball.shape)) {
        ball.shape.setPosition(lastPosition);
        ball.direction.y *= -1;
    }
}

void Game::EventBallSpawn()
{
    Ball &ball = m_balls.emplace_back();

    ball.shape.setFillColor(BALL_COLOR);
    ball.shape.setRadius(BALL_RADIUS);
    ball.shape.setPosition(gEngineConfig.windowSize.componentWiseMul({0.50f, 0.25f}));
    ball.shape.setOrigin(ball.shape.getGeometricCenter());

    ball.direction = {1, ctx.random.Angle(sf::Angle::Zero, sf::degrees(360))};
    ball.speed = BALL_SPEED;
}

void Game::EventBallMissed(int ballsMissed)
{
    m_stats.lives -= ballsMissed;
    m_stats.livesText.setString("Lives : " + std::to_string(m_stats.lives));

    if (m_stats.lives <= 0) {
        ctx.save.Set(STATS_HIGH_SCORE_KEY, m_stats.score);

        LOG_INFO("You Lose {} ", m_stats.score);

        ctx.scenes.RestartScene();
    }
}

void Game::HandleCollisions()
{
    HandleCollisionsPaddleBall();
    HandleCollisionsMap();
}

void Game::HandleCollisionsPaddleBall()
{
    for (auto &ball : m_balls) {
        if (ball.direction.y > 0 && IsShapeIntersects(ball.shape, m_paddle.shape)) {
            ResolveCollisionPaddleBall(ball);
        }
    }
}

void Game::ResolveCollisionPaddleBall(Ball &ball)
{
    ball.direction.y *= -1;
    m_sound.play();

    m_stats.score++;
    m_stats.scoreText.setString("Score : " + std::to_string(m_stats.score));
}

void Game::HandleCollisionsMap()
{
    int ballsMissed = std::erase_if(m_balls, [](auto &ball) {
        return IsShapeOutsideWindowBottom(ball.shape);
    });

    if (ballsMissed > 0) {
        EventBallMissed(ballsMissed);
    }
}
