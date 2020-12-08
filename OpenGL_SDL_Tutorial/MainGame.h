#pragma once

#include <SDL.h>
#include <glew.h>

#include <GLSLProgram.h>
#include <Errors.h>
#include <GLTexture.h>

#include <Sprite.h>
#include <vector>
#include <Window.h>
#include <NTCrystal.h>
#include <Camera2D.h>
#include <vector>
#include <SpriteBatch.h>
#include <InputManager.h>
#include <Timing.h>
#include "Bullet.h"

enum  class GameState {PLAY, EXIT};
enum class PlayerPos{LEFT, RIGHT, UP, DOWN};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();
private:
	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();
	void calculateFPS();

	NTCrystal::Window _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	NTCrystal::GLSLProgram _colorProgram;
	NTCrystal::Camera2D _camera;

	NTCrystal::SpriteBatch _spriteBatch;

	NTCrystal::InputManager _inputManager;
	NTCrystal::FpsLimiter _fpsLimiter;

	std::vector<Bullet> _bullets;

	float _time;
	float _fps;
	float _maxFPS;

	bool bulletSpawned;

	PlayerPos _playrPos;


};

