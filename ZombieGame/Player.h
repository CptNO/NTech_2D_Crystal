#pragma once
#include <vector>
#include "Human.h"
#include <InputManager.h>
#include <Camera2D.h>
#include "Bullet.h"

class Gun;

class Player : public Human
{
public:
	Player();
	~Player();

	void init(float speed, glm::vec2 pos, NTCrystal::InputManager *inputManager, NTCrystal::Camera2D *camera, std::vector<Bullet> *bullets);

	void addGun(Gun* gun);

	void update(const std::vector<std::string> &levelData,
		std::vector<Human*> &humans,
		std::vector<Zombie*> &zombies,
		float deltaTime) override;

	std::string getSelectedGun() const { return m_selectedGun; }

	bool isGunSelected() const { return (m_currentGunIndex != -1); }


private:
	NTCrystal::InputManager *m_inputManager;

	std::vector<Gun*> m_guns;
	int m_currentGunIndex;

	NTCrystal::Camera2D *m_camera;

	std::vector<Bullet> *m_bullets;
	
	std::string m_selectedGun;

	float m_velocity = 0.0f;
};

