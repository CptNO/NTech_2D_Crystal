#include "Gun.h"
#include <random>
#include <ctime>
#include <glm\gtx\rotate_vector.hpp>


Gun::Gun(std::string name, int fireRate, int bulletsPerShot, float spread, float bulletSpeed, float bulletDamage, NTCrystal::AudioEngine* audioEngine, std::string audioFileName) :
m_name(name),
m_fireRate(fireRate),
m_bulletsPerShot(bulletsPerShot),
m_spread(spread),
m_bulletSpead(bulletSpeed),
m_bulletDamage(bulletDamage),
m_frameCounter(0)

{
	m_gunSoundEffect = audioEngine->loadSoundEffect(audioFileName);
}


Gun::~Gun()
{
}

void Gun::update(bool isMouseDown, const glm::vec2 &position, const glm::vec2 &direction, std::vector<Bullet> &bullets)
{
	m_frameCounter++;
	if (m_frameCounter >= m_fireRate && isMouseDown)
	{
		fire(direction,position, bullets);
		m_frameCounter = 0;
	}
}

void Gun::fire(glm::vec2 direction, const glm::vec2 &position, std::vector<Bullet> &bullets){

	static std::mt19937 randomEngine(time(nullptr));
	std::uniform_real_distribution<float>randRotate(-m_spread, m_spread);


	for (int i = 0; i < m_bulletsPerShot; i++){

		bullets.emplace_back(position, 
			glm::rotate(direction, 
			randRotate(randomEngine)), 
			m_bulletDamage, 
			m_bulletSpead);
	}
	m_gunSoundEffect.play();
}
