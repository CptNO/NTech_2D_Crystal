#include "Agent.h"
#include <ResourceManager.h>
#include "Level.h"
#include <algorithm>

Agent::Agent()
{
}


Agent::~Agent()
{
}


void Agent::draw(NTCrystal::SpriteBatch &_spriteBatch)
{
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 destRect;
	destRect.x = m_position.x;
	destRect.y = m_position.y;
	destRect.z = AGENT_WIDTH;
	destRect.w = AGENT_WIDTH;

	if (m_frameCount >= 0 && m_isHit == true)
	{
		m_color.r = 200;
		m_color.b = 0;
		m_color.g = 0;
		m_color.r = 255;

		m_frameCount--;
	}
	else{


		m_color.r = 255;
		m_color.g = 255;
		m_color.b = 255;
		m_color.a = 255;

		m_isHit = false;
		m_dmgDelay = false;
	}

	_spriteBatch.draw(destRect, uvRect, m_textureID, 0.0f, m_color, m_direction);
}

bool Agent::applyDamage(float damage)
{
	if (m_dmgDelay == false){
		m_isHit = true;
		m_frameCount = 10;

		m_health -= damage;
		m_dmgDelay = true;
		if (m_health <= 0)
		{
			return true;
		}
	}
	return false;
}

void Agent::update(const std::vector<std::string> &levelData,
	std::vector<Human*> &humans,
	std::vector<Zombie*> &zombies,
	float deltaTime)
{
	//This function is implemented in classes that derive from agent
}

bool Agent::colideWithLevel(const std::vector<std::string> &levelData)
{
	std::vector<glm::vec2> collideTilePositions;
	checkTilePosition(collideTilePositions, levelData, m_position.x, m_position.y);
	checkTilePosition(collideTilePositions, levelData, m_position.x + AGENT_WIDTH, m_position.y);
	checkTilePosition(collideTilePositions, levelData, m_position.x, m_position.y + AGENT_WIDTH);
	checkTilePosition(collideTilePositions, levelData, m_position.x + AGENT_WIDTH, m_position.y + AGENT_WIDTH);	

	if (collideTilePositions.size() == 0)
		return false;

	//This is collision checking
	for (int i = 0; i < collideTilePositions.size(); i++)
	{
		collideWithTile(collideTilePositions[i]);
	}
	return true;
}

bool Agent::collideWithAgent(Agent *agent)
{
	const float MIN_DISTANCE = AGENT_RADIUS * 2.0f;

	glm::vec2 centerPosA = m_position + glm::vec2(AGENT_RADIUS);
	glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_RADIUS);

	glm::vec2 distVec = centerPosA - centerPosB;

	float distance = glm::length(distVec);

	float collisionDepth = MIN_DISTANCE - distance;
	if (collisionDepth > 0)
	{
		glm::vec2 collisonDepthVec = glm::normalize(distVec) * collisionDepth;
		m_position += collisonDepthVec / 2.0f;
		agent->m_position -= collisonDepthVec / 2.0f;
		return true;
	}
	else
		return false;
}

void Agent::checkTilePosition(std::vector<glm::vec2> &collideTilePositions,
	const std::vector<std::string> &levelData,
	float x, float y)
{
	//check 4 corners
	glm::vec2 cornerPos = glm::vec2(floor(x / (float)TILE_WIDTH),
		floor(y / (float)TILE_WIDTH));

	//if we are outside the world
	if (cornerPos.x < 0 || cornerPos.x >= levelData[0].length() ||
		cornerPos.y < 0 || cornerPos.y >= levelData.size()){
		return;
	}

	if (levelData[cornerPos.y][cornerPos.x] != '.' && levelData[cornerPos.y][cornerPos.x] != ',' && levelData[cornerPos.y][cornerPos.x] != 'P'
		&& levelData[cornerPos.y][cornerPos.x] != 'Z'  && levelData[cornerPos.y][cornerPos.x] != '@')
	{
		collideTilePositions.push_back(cornerPos  * (float)TILE_WIDTH + glm::vec2((float)TILE_WIDTH / 2));
	}
	
}

//AABB coallision algorthim
void Agent::collideWithTile(glm::vec2 tilePos)
{

	const float TILE_RADIUS = (float)TILE_WIDTH / 2.0f;	
	const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;

	// Center position of the agent
	glm::vec2 centerAgentPos = m_position + glm::vec2(AGENT_RADIUS);
	// Vector from the agent to the tile
	glm::vec2 distVec = centerAgentPos - tilePos;

	// Get the depth of the collision
	float xDepth = MIN_DISTANCE - abs(distVec.x);
	float yDepth = MIN_DISTANCE - abs(distVec.y);

	// If either the depths are > 0, then we collided
	if (xDepth > 0 && yDepth > 0) {

		// Check which collision depth is less
		if (std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f)) {
			// X collsion depth is smaller so we push in X direction
			if (distVec.x < 0) {
				m_position.x -= xDepth;
			}
			else {
				m_position.x += xDepth;
			}
		}
		else {
			// Y collsion depth is smaller so we push in X direction
			if (distVec.y < 0) {
				m_position.y -= yDepth;
			}
			else {
				m_position.y += yDepth;
			}
		}
	}
}

