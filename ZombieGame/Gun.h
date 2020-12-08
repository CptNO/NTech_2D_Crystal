#pragma once
#include <string>
#include <glm\glm.hpp>
#include <vector>
#include "Bullet.h"
#include <AudioEngine.h>

class Gun
{
public:
	Gun(std::string name, int fireRate, int bulletsPerShot, float spread, float bulletSpeed, float bulletDamage, NTCrystal::AudioEngine* audioEngine, std::string audioFileName);
	~Gun();

	void update(bool isMouseDown, const glm::vec2 &position,
		const glm::vec2 &direction,
		std::vector<Bullet> &bullets);

	std::string getGunName() const { return m_name; }

private:

	void fire(glm::vec2 direction, const glm::vec2 &position, std::vector<Bullet> &bullets);


	std::string m_name;

	int m_fireRate; ///< firrate in terms of frame
	int m_bulletsPerShot;

	float m_spread; ///< acuracy

	float m_bulletSpead; 

	float m_bulletDamage;

	int m_frameCounter;

	//sound effects
	NTCrystal::SoundEffect m_gunSoundEffect;
};

