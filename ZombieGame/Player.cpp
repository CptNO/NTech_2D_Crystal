#include "Player.h"
#include <SDL.h>
#include "Gun.h"
#include <iostream>
#include <ResourceManager.h>


Player::Player() :
	m_currentGunIndex(-1)
{
}


Player::~Player()
{
}

void Player::init(float speed, glm::vec2 pos, NTCrystal::InputManager *inputManager, NTCrystal::Camera2D *camera, std::vector<Bullet> *bullets)
{
	m_speed = speed;
	m_position = pos;
	m_inputManager = inputManager;
	m_camera = camera;
	m_bullets = bullets;

	m_color.r = 255;
	m_color.g = 255;
	m_color.b = 150;
	m_color.a = 255;

	m_health = 150;

	m_selectedGun = "none";

	m_textureID =  NTCrystal::ResourceManager::getTexture("Textures/player.png").id;
}

void Player::addGun(Gun *gun)
{
	m_guns.push_back(gun);

	if (m_currentGunIndex == -1){
		m_currentGunIndex = 0;
		m_selectedGun = m_guns[0]->getGunName();
	}
}

void Player::update(const std::vector<std::string> &levelData,

	std::vector<Human*> &humans,
	std::vector<Zombie*> &zombies,
	float deltaTime)
{



	if (m_inputManager->isKeyDown(SDLK_w)){
		m_position.y += m_speed * deltaTime;
	}
	if (m_inputManager->isKeyDown(SDLK_s)){
		m_position.y -= m_speed * deltaTime;
	}
	if (m_inputManager->isKeyDown(SDLK_a)){
		m_position.x -= m_speed * deltaTime;
	}
	if (m_inputManager->isKeyDown(SDLK_d)){
		m_position.x += m_speed * deltaTime;
		
	}
	if (m_inputManager->isKeyDown(SDLK_1) && m_guns.size() >= 0 ){
		m_currentGunIndex = 0;
		m_selectedGun = m_guns[0]->getGunName();
	}
	else if (m_inputManager->isKeyDown(SDLK_2) && m_guns.size() >= 0){
		m_currentGunIndex = 1;
		m_selectedGun = m_guns[1]->getGunName();
	}
	else if (m_inputManager->isKeyDown(SDLK_3) && m_guns.size() >= 0){
		m_currentGunIndex = 2;
		m_selectedGun = m_guns[2]->getGunName();
	}
	//mouse
	if (m_inputManager->isKeyDown(SDL_BUTTON_LEFT)){

	}


	glm::vec2 mouseCords = m_inputManager->getMouseCords();
	mouseCords = m_camera->convertScreenToWorld(mouseCords);

	glm::vec2 centerPosition = m_position + glm::vec2(AGENT_RADIUS);
	m_direction = glm::normalize(mouseCords - centerPosition);


	if (m_currentGunIndex != -1)
	{
		//is key down will let us shout while holding mouse button while is key pressed will only let us once
		m_guns[m_currentGunIndex]->update(m_inputManager->isKeyDown(SDL_BUTTON_LEFT), 
			centerPosition,
			m_direction,
			*m_bullets
			);
	}

	colideWithLevel(levelData);
}



