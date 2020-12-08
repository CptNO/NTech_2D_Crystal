#pragma once
#include <string>
#include <vector>
#include <SpriteBatch.h>
#include <ResourceManager.h>

const int TILE_WIDTH = 64;

class Level
{
public:
	//constructor will build and load level
	Level(const std::string filename);
	~Level();

	void draw();

	void update();

	void loadLevel(std::string filename);


	//getters
	int getNumHumans() const { return m_numHumans;  }
	const std::vector<std::string> &getLevelData() const { return m_levelData; }	//getters 
	glm::vec2 startPlayerPos() const { return m_startPlayerPos; }
	const std::vector<glm::vec2>& startZombiePos() const { return m_zombieStartPos; }
	int getWidth() const { return m_levelData[0].size(); }
	int getHeight() const { return m_levelData.size(); }

private:

	void populateLevel();

	std::vector<std::string> m_levelData;

	int m_numHumans;
	
	NTCrystal::SpriteBatch m_spriteBatch;

	glm::vec2 m_startPlayerPos;
	std::vector<glm::vec2> m_zombieStartPos;
};

