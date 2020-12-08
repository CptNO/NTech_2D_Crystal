#include "Zombie.h"
#include "Human.h"
#include <ResourceManager.h>


Zombie::Zombie()
{
}


Zombie::~Zombie()
{
}

void Zombie::init(float speed, glm::vec2 pos)
{
	m_speed = speed;
	m_position = pos;
	m_health = 100;

	m_frameCount = 0;
	m_isHit = false;

	m_color = NTCrystal::ColorRGBA8(255, 255, 255, 255);

	m_textureID = NTCrystal::ResourceManager::getTexture("Textures/zombie.png").id;
}

void Zombie::update(const std::vector<std::string> &levelDate,
	std::vector<Human*> &humans,
	std::vector<Zombie*> &zombie,
	float deltaTime)
{
	Human *closestHuman = getNearestHuman(humans);
	if (closestHuman != nullptr)
	{
		m_direction = glm::normalize( closestHuman->getPosition() - m_position);

		m_position += (m_direction * m_speed) * deltaTime;

	}


	if (colideWithLevel(levelDate));
}

Human* Zombie::getNearestHuman(std::vector<Human*> &humans)
{
	Human *closesHuman = nullptr;
	float smalestDistance = 9999999.0f;

	for (int i = 0; i < humans.size(); i++)
	{
		glm::vec2 distVec = humans[i]->getPosition() - m_position;
		float distance = glm::length(distVec);

		if (distance < smalestDistance)
		{
			smalestDistance = distance;
			closesHuman = humans[i];
		}
	}

	return closesHuman;

}
