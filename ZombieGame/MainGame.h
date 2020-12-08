#pragma once

//OpenGL include
#include <glew.h>
#include <freeglut.h>

//SDL include
#include <SDL.h>
#include <SDL_ttf.h>

//NTCrystal(my engine) engine include
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
#include "Level.h"
#include "Player.h"
#include "Bullet.h"

//enum
enum  GameState
{
	EXIT,
	VICTORY,
	DEFEAT,
	PLAY
};

class MainGame
{
public:
	MainGame();
	~MainGame();

	//runs the game
	void run();

private:
	// init core systems
	void initSystems();

	//init shaders
	void initShaders();

	//main game loop 
	void gameLoop();

	//processes player input
	void procesInput();

	//draws objects
	void drawGame();

	void drawHud(); ///< draws heads up display

	void update(float deltaTime);

	//updates all agents
	void updateAgents(float deltaTime);

	void updateBullets(float deltaTime);

	void initLevel();//init s level and sets up everything

	void checkVictory();

	//loads next level
	void loadNewLevel();

	void updateParticleEngine(float deltaTime);

	void addBlood(const glm::vec2 &position, int numParticles);

	GameState m_gameState; //sets current game state

	NTCrystal::Window m_window; //game window

	NTCrystal::GLSLProgram m_textureProgram; //Shader program

	NTCrystal::InputManager m_inputManager; //input manager

	NTCrystal::Camera2D m_camera; //main camera

	NTCrystal::Camera2D m_hudCamera;

	NTCrystal::FpsLimiter m_fpsLimiter;

	NTCrystal::SpriteBatch m_ObjectSpriteBatch;

	NTCrystal::SpriteBatch m_hudSpriteBatch;

	NTCrystal::ParticleEngine2D m_particleEngine;

	NTCrystal::ParticleBatch2D *m_bloodParticleBatch;

	std::vector<Level*> m_levels;

	Player *m_player;
	std::vector<Human*> m_humans;
	std::vector<Zombie*> m_zombies;
	std::vector<Bullet> m_bullets;

	float m_screenWidth;
	float m_screenHeight;

	int m_currentLevel;

	int m_numHumansKilled = 0;
	int m_numZombiesKilled = 0;

	NTCrystal::SpriteFont *m_spriteFont;

	NTCrystal::AudioEngine m_audioEngine;

	NTCrystal::Music m_currentLevelMusic;

	NTCrystal::SoundEffect m_DefeatSoundEfect;
	NTCrystal::SoundEffect m_VictorySoundEfect;

	bool m_playEnd;

	float m_fps;
	bool m_exitMenu = false;
};

