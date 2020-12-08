#include "Human.h"
#include <random>
#include <ctime>
#include <glm\gtx\rotate_vector.hpp>
#include <ResourceManager.h>


Human::Human() : m_frames(0)
{
}


Human::~Human()
{
}

void Human::update(const std::vector<std::string> &levelData,
	std::vector<Human*> &humans,
	std::vector<Zombie*> &zombies,
	float deltaTime)
{

	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float>randRotate(-1.0f, 1.0f);

	m_position += (m_direction * m_speed) * deltaTime;

	//randmoly change dir every 20 frames 
	if (m_frames == 20){
		m_direction = glm::rotate(m_direction, randRotate(randomEngine));
		m_frames = 0;
	}
	else
		m_frames++;

	if (colideWithLevel(levelData))
	{
		m_direction = glm::rotate(m_direction, randRotate(randomEngine));
	}

}

void Human::init(float speed, glm::vec2 pos)
{
	static std::mt19937 randomEngine(time(nullptr));

	static std::uniform_real_distribution<float>randDir(-1.0f, 2.0f);

	m_color.r = 255;
	m_color.g = 255;
	m_color.b = 255;
	m_color.a = 255;

	m_health = 50;

	m_frameCount = 0;
	m_isHit = false;

	m_speed = speed;
	m_position = pos;
	//get random dir
	m_direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
	//make shure is not 0
	if (m_direction.length() == 0) m_direction = glm::vec2(1.0f, 0.0f);

	m_direction = glm::normalize(m_direction);

	m_textureID = NTCrystal::ResourceManager::getTexture("Textures/human.png").id;

}