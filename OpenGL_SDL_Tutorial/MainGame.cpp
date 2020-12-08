#include "MainGame.h"
#include <Errors.h>

#include <iostream>
#include <string>
#include <freeglut.h>
#include <ResourceManager.h>


MainGame::MainGame()
{
	_screenWidth = 1024;
	_screenHeight = 800;
	_time = 0.0;
	_gameState = GameState::PLAY;
	_maxFPS = 60.0f;
	_camera.init(_screenWidth, _screenHeight);
	_playrPos = PlayerPos::UP;

}


MainGame::~MainGame()
{

}

//This will run game
void MainGame::run()
{
	initSystems();

	/*
	//Bottom left corner
	_sprites.push_back(new NTCrystal::Sprite());
	_sprites.back()->init(0.0f, 0.0f, _screenWidth / 2, _screenWidth / 2, "Textures/PNG/CharacterRight_Standing.png");



	//upper right corner
	_sprites.push_back(new NTCrystal::Sprite());
	_sprites.back()->init(_screenWidth / 2, 0.0f, _screenWidth / 2, _screenWidth / 2, "Textures/PNG/CharacterLeft_Standing.png");


	//upper left corner
	_sprites.push_back(new NTCrystal::Sprite());
	_sprites.back()->init(-700, 200, _screenWidth / 2, _screenWidth / 2, "Textures/PNG/CharacterLeft_Standing.png");


	//botom right corner
	_sprites.push_back(new NTCrystal::Sprite());
	_sprites.back()->init(50, 100, _screenWidth / 2, _screenWidth / 2, "Textures/PNG/CharacterLeft_Standing.png");

	_sprites.push_back(new NTCrystal::Sprite());
	_sprites.back()->init(200, -500, _screenWidth / 2, _screenWidth / 2, "Textures/PNG/CharacterLeft_Standing.png");
	*/

	//"Textures/PNG/CharacterRight_Standing.png"

	//this will only return when game ends
	gameLoop();
}

void MainGame::initSystems()
{
	NTCrystal::init();
	//Opens SDL window

	_window.create("NTech_2D_Crystal", _screenWidth, _screenHeight, 0);
	initShaders();

	_spriteBatch.init();
	_fpsLimiter.init(_maxFPS);

}

void MainGame::initShaders()
{
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

void MainGame::gameLoop()
{
	//this has to be updated
	while (_gameState != GameState::EXIT) {

		_fpsLimiter.begin();

		processInput();
		_time += 0.1;

		_camera.update();

		for (int i = 0; i < _bullets.size();)
		{
			if (_bullets[i].update() == true){
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
			}
			else
			{
				i++;
			}
		}

		drawGame();

		_fps = _fpsLimiter.end();

		//print only once every 10 frames
		static int frameCounter = 0;
		frameCounter++;
		if (bulletSpawned)
		{
			std::cout << "Bullet number: " + std::to_string(_bullets.size()) << std::endl;
			bulletSpawned = false;
		}

		if (frameCounter == 1000){
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}


	}
}

void MainGame::processInput() {
	SDL_Event evnt;

	const float CAMERA_SPEED = 2.0f;
	const float SCALE_SPEED = 0.1f;


	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCords(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			std::cout << "kex pressed" << std::endl;
			_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(evnt.button.button);
			break;
		}
	}

	if (_inputManager.isKeyPressed(SDLK_ESCAPE)){

		std::cout << "Escape Pressed" << std::endl;
		_gameState = GameState::EXIT;
	}
	if (_inputManager.isKeyPressed(SDLK_w)){

		std::cout << "W Pressed" << std::endl;
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
		_playrPos = PlayerPos::UP;
	}
	if (_inputManager.isKeyPressed(SDLK_s)){

		std::cout << "s Pressed" << std::endl;
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
		_playrPos = PlayerPos::DOWN;
	}
	if (_inputManager.isKeyPressed(SDLK_a)){

		std::cout << "a Pressed" << std::endl;
		_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
		_playrPos = PlayerPos::LEFT;
	}
	if (_inputManager.isKeyPressed(SDLK_d)){

		std::cout << "d Pressed" << std::endl;
		_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
		_playrPos = PlayerPos::RIGHT;
	}
	if (_inputManager.isKeyPressed(SDLK_q)){

		std::cout << "q Pressed" << std::endl;
		_camera.setScale(_camera.getScale() *(1 - SCALE_SPEED));
	}
	if (_inputManager.isKeyPressed(SDLK_e)){
		std::cout << "e Pressed" << std::endl;
		_camera.setScale(_camera.getScale() *(1 + SCALE_SPEED));
	}
	//mouse
	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)){

		glm::vec2 mouseCords = _inputManager.getMouseCords();
		mouseCords = _camera.convertScreenToWorld(mouseCords);


		glm::vec2 playerPosition(_camera.getPosition().x, _camera.getPosition().y);
		glm::vec2 direction = mouseCords - playerPosition;
		direction = glm::normalize(direction);

		_bullets.emplace_back(playerPosition, direction, 2.0f, 1000);

		bulletSpawned = true;

		//std::cout << " X:" + std::to_string(mouseCords.x) + "  Y:" + std::to_string(mouseCords.y) + "\n";
	}

}

void MainGame::drawGame()
{


	//sets base depth to 1.0
	glClearDepth(1.0);

	//Clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Enable shader
	_colorProgram.use();

	//use texture unit 0
	glActiveTexture(GL_TEXTURE0);

	//bind texture to texture unit 0
	//glBindTexture(GL_TEXTURE_2D, _playerTexture.id);

	//get uniform location
	GLint textureLocation = _colorProgram.getUniformLocation("sampler");
	//tell shader texture  is in unit 0
	glUniform1i(textureLocation, 0);


	//Set time location
	/*GLuint  timeLocation = _colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time);
	*/

	//set camera matrix
	GLuint  pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	_spriteBatch.begin();

	glm::vec4 pos(_camera.getPosition().x, _camera.getPosition().y, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	NTCrystal::GLTexture texture;

	switch (_playrPos)
	{
	case PlayerPos::LEFT:
		texture = NTCrystal::ResourceManager::getTexture("Textures/PNG/CharacterLeft_Walk2.png");
		break;
	case PlayerPos::RIGHT:
		texture = NTCrystal::ResourceManager::getTexture("Textures/PNG/CharacterRight_Walk2.png");
		break;
	case PlayerPos::UP:
		texture = NTCrystal::ResourceManager::getTexture("Textures/PNG/CharacterRight_Standing.png");
		break;
	case PlayerPos::DOWN:
		texture = NTCrystal::ResourceManager::getTexture("Textures/PNG/CharacterRight_Standing.png");
		break;
	default:
		break;
	}


	NTCrystal::Color color;
	color.r = 255;
	color.b = 255;
	color.g = 255;
	color.a = 255;

	_spriteBatch.draw(pos, uv, texture.id, 0.0f, color);

	for (int i = 0; i < _bullets.size(); i++)
	{
		_bullets[i].draw(_spriteBatch);
	}

	/*
	for (int i = 0; i < 1000; i++) {
	_spriteBatch.draw(pos, uv, texture.id, 0.0f, color);
	_spriteBatch.draw(pos + glm::vec4(50, 0, 0, 0), uv, texture.id, 0.0f, color);
	}*/

	_spriteBatch.end();

	_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);

	_colorProgram.unuse();

	//swap buffer to draw everything on screen
	_window.swapBuffer();
}





