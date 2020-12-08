#include <NTCrystal.h>
#include <Window.h>
#include <GLSLProgram.h>
#include <InputManager.h>
#include <Camera2D.h>
#include <Timing.h>
#include <SpriteBatch.h>
#include <ResourceManager.h>
#include <SpriteFont.h>
#include <GLTexture.h>
#include <NTErrors.h>
#include <AudioEngine.h>
#include <ParticleEngine2D.h>
#include <ParticleBatch2D.h>
#include <Vertex.h>

//Basic include
#include <vector>
#include <string>
#include <iostream>

enum GameState
{
	EXIT,
	VICTORY,
	DEFEAT,
	PAUSE_MENU,
	MAIN_MENU,
	PLAY
};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	void initSystem();

	void initShaders();

	void gameLoop();

	void processInput();

	void drawGame();

	void update(float deltaTime);

	void updateEntites(float deltaTime);

	void initLEvel();

	void checkVicotry();

	void drawHud();

	GameState m_gameState;

	int m_lastPlayerBallTouch; //if check victory is true then last player who tuched the ball is winner

	int m_currentFPS;

	int m_fps;

	NTCrystal::Window m_window; //game window

	NTCrystal::GLSLProgram m_textureProgram; //Shader program

	NTCrystal::InputManager m_inputManager; //input manager

	NTCrystal::Camera2D m_camera; //main camera

	NTCrystal::Camera2D m_hudCamera;

	NTCrystal::FpsLimiter m_fpsLimiter;

	NTCrystal::SpriteBatch m_ObjectSpriteBatch;

	NTCrystal::SpriteBatch m_hudSpriteBatch;

	NTCrystal::SpriteBatch m_spriteBatch;

	NTCrystal::SpriteFont *m_spriteFont;



};
