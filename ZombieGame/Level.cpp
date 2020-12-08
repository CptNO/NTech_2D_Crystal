#include "Level.h"
#include <NTErrors.h>
#include <fstream>
#include <iostream>


Level::Level(const std::string filename)
{
	std::ifstream file;
	file.open(filename);

	if (file.fail()){
		NTCrystal::fatalError("fail to open " + filename);
	}

	//throw away first string in temp
	std::string temp;
	file >> temp >> m_numHumans;

	std::getline(file, temp); //throw avay first line


	while (std::getline(file, temp)){
		m_levelData.push_back(temp);
	}

	m_spriteBatch.init();

	m_spriteBatch.begin();

	glm::vec4 uvRect(0.0, 0.0, 1.0f, 1.0f);
	NTCrystal::ColorRGBA8 whiteColor;

	whiteColor.r = 255;
	whiteColor.g = 255;
	whiteColor.b = 255;
	whiteColor.a = 255;

	for (int y = 0; y < m_levelData.size(); y++)
	{
		for (int x = 0; x < m_levelData[y].size(); x++)
		{
			//get dest rect 
			glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

			//grab tile and process
			char tile = m_levelData[y][x];
			switch (tile)
			{
			case 'R':
				m_spriteBatch.draw(destRect, uvRect,
					NTCrystal::ResourceManager::getTexture("Textures/red_bricks.png").id,
					0.0f,
					whiteColor);
				break;
			case 'B':
				m_spriteBatch.draw(destRect, uvRect,
					NTCrystal::ResourceManager::getTexture("Textures/red_bricks.png").id,
					0.0f,
					whiteColor);
				break;
			case 'G':
				m_spriteBatch.draw(destRect, uvRect,
					NTCrystal::ResourceManager::getTexture("Textures/glass.png").id,
					0.0f,
					whiteColor);
				break;
			case 'L':
				m_spriteBatch.draw(destRect, uvRect,
					NTCrystal::ResourceManager::getTexture("Textures/light_bricks.png").id,
					0.0f,
					whiteColor);
				break;
			case '@':
				m_levelData[y][x] = '.'; // so we dont colide with player 
				m_startPlayerPos.x = x * TILE_WIDTH;
				m_startPlayerPos.y = y * TILE_WIDTH;

				//this will check if tile is concreate or pawent
				if (m_levelData[y - 1][x - 1] == '.' && m_levelData[y + 1][x + 1] == '.' && m_levelData[y + 1][x - 1] == '.'
					&& m_levelData[y - 1][x + 1] == '.' && m_levelData[y][x - 1] == '.' && m_levelData[y - 1][x] == '.' &&
					m_levelData[y + 1][x] == '.' && m_levelData[y][x + 1] == '.'){

					m_spriteBatch.draw(destRect, uvRect,
						NTCrystal::ResourceManager::getTexture("Textures/asphalt.png").id,
						0.0f,
						whiteColor);
				}
				else
				{
					m_spriteBatch.draw(destRect, uvRect,
						NTCrystal::ResourceManager::getTexture("Textures/tiles_mini.png").id,
						0.0f,
						whiteColor);
				}
				break;
			case 'Z':
				m_levelData[y][x] = '.'; // so we dont colide with z
				m_zombieStartPos.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);

				//this will check if tile is concreate or pawent
				if (m_levelData[y - 1][x - 1] == '.' && m_levelData[y + 1][x + 1] == '.' && m_levelData[y + 1][x - 1] == '.'
					&& m_levelData[y - 1][x + 1] == '.' && m_levelData[y][x - 1] == '.' && m_levelData[y - 1][x] == '.' &&
					m_levelData[y + 1][x] == '.' && m_levelData[y][x + 1] == '.'){

					m_spriteBatch.draw(destRect, uvRect,
						NTCrystal::ResourceManager::getTexture("Textures/asphalt.png").id,
						0.0f,
						whiteColor);
				}
				else
				{
					m_spriteBatch.draw(destRect, uvRect,
						NTCrystal::ResourceManager::getTexture("Textures/tiles_mini.png").id,
						0.0f,
						whiteColor);
				}
				break;
			case ',':
				m_spriteBatch.draw(destRect, uvRect,
					NTCrystal::ResourceManager::getTexture("Textures/tiles_mini.png").id,
					0.0f,
					whiteColor);
				break;
			case '.':
				m_spriteBatch.draw(destRect, uvRect,
					NTCrystal::ResourceManager::getTexture("Textures/asphalt.png").id,
					0.0f,
					whiteColor);
				break;
			case 'P':
				m_spriteBatch.draw(destRect, uvRect,
					NTCrystal::ResourceManager::getTexture("Textures/grass.png").id,
					0.0f,
					whiteColor);
				break;
			default:
				std::printf("unexpected symbol: %c at(%d, %d)", tile, x, y);
				break;
			}
		}
	}


	m_spriteBatch.end();
}


Level::~Level()
{
}


void Level::draw()
{

	m_spriteBatch.renderBatch();
}

void Level::loadLevel(std::string filename)
{
	std::ifstream file;
	file.open(filename);

	if (file.fail()){
		NTCrystal::fatalError("fail to open " + filename);
	}

	//throw away first string in temp
	std::string temp;
	file >> temp >> m_numHumans;

	std::getline(file, temp); //throw avay first line


	while (std::getline(file, temp)){
		m_levelData.push_back(temp);
	}

	m_spriteBatch.init();

	m_spriteBatch.begin();

	glm::vec4 uvRect(0.0, 0.0, 1.0f, 1.0f);
	NTCrystal::ColorRGBA8 whiteColor;

	whiteColor.r = 255;
	whiteColor.g = 255;
	whiteColor.b = 255;
	whiteColor.a = 255;

	for (int y = 0; y < m_levelData.size(); y++)
	{
		for (int x = 0; x < m_levelData[y].size(); x++)
		{
			//get dest rect 
			glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

			//grab tile and process
			char tile = m_levelData[y][x];
			switch (tile)
			{
			case 'R':
				m_spriteBatch.draw(destRect, uvRect,
					NTCrystal::ResourceManager::getTexture("Textures/red_bricks.png").id,
					0.0f,
					whiteColor);
				break;
			case 'B':
				m_spriteBatch.draw(destRect, uvRect,
					NTCrystal::ResourceManager::getTexture("Textures/red_bricks.png").id,
					0.0f,
					whiteColor);
				break;
			case 'G':
				m_spriteBatch.draw(destRect, uvRect,
					NTCrystal::ResourceManager::getTexture("Textures/glass.png").id,
					0.0f,
					whiteColor);
				break;
			case 'L':
				m_spriteBatch.draw(destRect, uvRect,
					NTCrystal::ResourceManager::getTexture("Textures/light_bricks.png").id,
					0.0f,
					whiteColor);
				break;
			case '@':
				m_levelData[y][x] = '.'; // so we dont colide with player 
				m_startPlayerPos.x = x * TILE_WIDTH;
				m_startPlayerPos.y = y * TILE_WIDTH;

				//this will check if tile is concreate or pawent
				if (m_levelData[y - 1][x - 1] == '.' && m_levelData[y + 1][x + 1] == '.' && m_levelData[y + 1][x - 1] == '.'
					&& m_levelData[y - 1][x + 1] == '.' && m_levelData[y][x - 1] == '.' && m_levelData[y - 1][x] == '.' &&
					m_levelData[y + 1][x] == '.' && m_levelData[y][x + 1] == '.'){

					m_spriteBatch.draw(destRect, uvRect,
						NTCrystal::ResourceManager::getTexture("Textures/asphalt.png").id,
						0.0f,
						whiteColor);
				}
				else
				{
					m_spriteBatch.draw(destRect, uvRect,
						NTCrystal::ResourceManager::getTexture("Textures/tiles_mini.png").id,
						0.0f,
						whiteColor);
				}
				break;
			case 'Z':
				m_levelData[y][x] = '.'; // so we dont colide with z
				m_zombieStartPos.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);

				//this will check if tile is concreate or pawent
				if (m_levelData[y - 1][x - 1] == '.' && m_levelData[y + 1][x + 1] == '.' && m_levelData[y + 1][x - 1] == '.'
					&& m_levelData[y - 1][x + 1] == '.' && m_levelData[y][x - 1] == '.' && m_levelData[y - 1][x] == '.' &&
					m_levelData[y + 1][x] == '.' && m_levelData[y][x + 1] == '.'){

					m_spriteBatch.draw(destRect, uvRect,
						NTCrystal::ResourceManager::getTexture("Textures/asphalt.png").id,
						0.0f,
						whiteColor);
				}
				else
				{
					m_spriteBatch.draw(destRect, uvRect,
						NTCrystal::ResourceManager::getTexture("Textures/tiles_mini.png").id,
						0.0f,
						whiteColor);
				}
				break;
			case ',':
				m_spriteBatch.draw(destRect, uvRect,
					NTCrystal::ResourceManager::getTexture("Textures/tiles_mini.png").id,
					0.0f,
					whiteColor);
				break;
			case '.':
				m_spriteBatch.draw(destRect, uvRect,
					NTCrystal::ResourceManager::getTexture("Textures/asphalt.png").id,
					0.0f,
					whiteColor);
				break;
			case 'P':
				m_spriteBatch.draw(destRect, uvRect,
					NTCrystal::ResourceManager::getTexture("Textures/grass.png").id,
					0.0f,
					whiteColor);
				break;
			default:
				std::printf("unexpected symbol: %c at(%d, %d)", tile, x, y);
				break;
			}
		}
	}


	m_spriteBatch.end();
}
