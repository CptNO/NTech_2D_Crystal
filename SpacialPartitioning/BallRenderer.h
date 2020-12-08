#pragma once

#include <SpriteBatch.h>
#include "Ball.h"

class BallRenderer {
public:
    void renderBall(NTCrystal::SpriteBatch& spriteBatch, Ball& ball);
};
