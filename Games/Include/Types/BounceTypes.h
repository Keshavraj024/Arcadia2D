#pragma once

#include "Config/BounceConfig.h"

namespace Bounce {

enum Action : std::int8_t { MOVELEFT, MOVERIGHT };

struct Paddle
{
    sf::RectangleShape shape;
    float speed;
};

struct Ball
{
    sf::CircleShape shape;
    sf::Vector2f direction;
    float speed;
};

struct GameStats
{
    int score;
    int highScore;
    int lives;

    sf::Text scoreText{GetDefaultFont()};
    sf::Text highScoreText{GetDefaultFont()};
    sf::Text livesText{GetDefaultFont()};
};
} // namespace Bounce
