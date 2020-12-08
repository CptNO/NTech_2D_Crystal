#pragma once
#include <vector>
#include <glm\glm.hpp>
#include <GLTexture.h>
#include <SpriteBatch.h>

const float AGENT_WIDTH = 50;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;

class Zombie;
class Human;

class Agent
{
public:
	Agent();
	virtual ~Agent();

	//ovo znaci da svaka klasa koj nasljeduje ovu klasu mora imat svoju update funkciju
	virtual void update(const std::vector<std::string> &levelData,
						std::vector<Human*> &humans, 
						std::vector<Zombie*> &zombies,
						float deltaTime) = 0;

	bool colideWithLevel(const std::vector<std::string> &levelData);
	
	bool collideWithAgent(Agent *agent);

	//return true if agent is dead
	bool applyDamage(float damage);

	void draw(NTCrystal::SpriteBatch &_spriteBatch);

	glm::vec2 getPosition() const { return m_position; }


protected:

	void checkTilePosition(std::vector<glm::vec2> &collideTilePositions,
		const std::vector<std::string> &levelData,
		float x, float y);

	void collideWithTile(glm::vec2 tilePos);

	glm::vec2 m_position;
	glm::vec2 m_direction = glm::vec2(1.0f, 0.0f);
	float m_speed;
	float m_health;

	GLuint m_textureID;
	NTCrystal::ColorRGBA8 m_color;

	bool m_isHit;
	int m_frameCount;
	bool m_dmgDelay;

	glm::vec2 m_targetDirection;
};

