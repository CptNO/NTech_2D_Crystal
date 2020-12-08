#pragma once

#include <Camera2D.h>
#include <SpriteBatch.h>
#include <InputManager.h>
#include <Window.h>
#include <GLSLProgram.h>
#include <Timing.h>
#include <SpriteFont.h>
#include <memory>

#include "BallController.h"
#include "BallRenderer.h"
#include "Grid.h"

enum class GameState { RUNNING, EXIT };

const int CELL_SIZE = 12;

class MainGame {
public:
    ~MainGame();
    void run();


private:
    void init();
    void initBalls();
    void update(float deltaTime);
    void draw();
    void drawHud();
    void processInput();

    int m_screenWidth = 0;
    int m_screenHeight = 0;

    std::vector<Ball> m_balls; ///< All the balls
    std::unique_ptr<Grid> m_grid; ///< Grid for spatial partitioning for collision

    BallController m_ballController; ///< Controls balls
    BallRenderer m_ballRenderer; ///< Renders balls

    NTCrystal::Window m_window; ///< The main window
    NTCrystal::SpriteBatch m_spriteBatch; ///< Renders all the balls
    std::unique_ptr<NTCrystal::SpriteFont> m_spriteFont; ///< For font rendering
    NTCrystal::Camera2D m_camera; ///< Renders the scene
    NTCrystal::InputManager m_inputManager; ///< Handles input
    NTCrystal::GLSLProgram m_textureProgram; ///< Shader for textures]

    NTCrystal::FpsLimiter m_fpsLimiter; ///< Limits and calculates fps
    float m_fps = 0.0f;

    GameState m_gameState = GameState::RUNNING; ///< The state of the game
};

