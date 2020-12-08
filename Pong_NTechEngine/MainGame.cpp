#include "MainGame.h"
#include <glut.h>
#include "MainGameConsts.h"
#include <algorithm>
#include <glm/gtx/rotate_vector.hpp>
#include <random>
#include <ctime>
#include <string> 

MainGame::~MainGame(){
	//TO DO: clean all memory
}

MainGame::MainGame(){

}

void MainGame::run(){
	initSystem();

	gameLoop();

}

void MainGame::initSystem(){
	NTCrystal::init();
	m_window.create("Starting window Pong game", 1280, 960, NTCrystal::BORDERLESS);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	initShaders();


	m_camera.init(1280, 960);
	m_camera.setScale(2.0f);

	m_fpsLimiter.init(MAX_FPS);
}

void MainGame::gameLoop(){

	float _previusTicks = SDL_GetTicks();
	

	while (!m_gameState == GameState::EXIT){
		m_fpsLimiter.begin();

		float _deltaTime;
		float _newTicks = SDL_GetTicks();
		float _frameTime = _newTicks - _previusTicks;
		_previusTicks = _newTicks;
		float totalDeltaTime = _frameTime / DESIRED_FRAMETIME;

		m_inputManager.update();

		processInput();

		int i = 0;

		while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS){
			_deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
			//update(_deltaTime);
			totalDeltaTime -= _deltaTime;
			i++;
		}

		
		drawGame();
		
	}	
}

void MainGame::processInput(){
	SDL_Event keyEvent;

	while (SDL_PollEvent(&keyEvent)){
		std::cout << " Key event occured: " + std::to_string(keyEvent.key.keysym.sym);
		switch (keyEvent.type)
		{
		case SDL_QUIT:
			if (m_gameState == GameState::PAUSE_MENU){
				m_gameState = GameState::EXIT;
			}
			else
				m_gameState = GameState::PAUSE_MENU;
			break;
		default:
			break;
		}
	}
}

void MainGame::drawGame(){
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_textureProgram.use();
	
	m_textureProgram.use();

	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = m_textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	GLuint  pLocation = m_textureProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = m_camera.getCameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
	
	m_window.swapBuffer();
	std::cout << "\n Rendering batch";
}

void MainGame::drawHud() {
	const NTCrystal::ColorRGBA8 fontColor(255, 0, 0, 255);
	// Convert float to char *
	char buffer[64];
	sprintf(buffer, "%.1f", m_fps);

	
	m_hudSpriteBatch.begin();
	m_spriteFont->draw(m_hudSpriteBatch, buffer, glm::vec2(0.0f, 1920 - 32.0f),
		glm::vec2(1.0f), 0.0f, fontColor);
	m_hudSpriteBatch.end();
	m_spriteBatch.renderBatch();
	
}

void MainGame::initShaders(){
	m_textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	m_textureProgram.addAttribute("vertexPosition");
	m_textureProgram.addAttribute("vertexColor");
	m_textureProgram.addAttribute("vertexUV");
	m_textureProgram.linkShaders();
	
}