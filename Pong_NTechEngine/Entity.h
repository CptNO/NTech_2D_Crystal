#pragma once
#include <vector>
#include <glm\glm.hpp>
#include <GLTexture.h>
#include <SpriteBatch.h>


class Entity{

public:
	Entity();
	~Entity();

	virtual void update(float deltaTime) = 0;
	void collideWithLevel(const std::vector<std::string> &levelBounds);
	void collideWithEntity(Entity *ntity);
	glm::vec2 getPosition() const { return m_position; }
	void draw(NTCrystal::SpriteBatch &m_spriteBatch);
		
private:
	glm::vec2 m_position;
	double m_speed;


};