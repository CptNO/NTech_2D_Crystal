#include "MainGame.h"

#include "Zombie.h"
#include <random>
#include <ctime>
#include "Gun.h"
#include <algorithm>
#include <glm/gtx/rotate_vector.hpp>


/*HINTS TO DO: Smoothen up entity rotation by keeping track of new rotation and increasing it each frame

				*/
const float ZOMBIE_SPEED = 2.0f;
const float HUMAN_SPEED = 1.5f;
const float PLAYER_SPEED = 15.0f;

const float MS_PER_SECOND = 1000;
const float DESIRED_FRAMETIME = 60.0f;
const float MAX_FPS = MS_PER_SECOND / DESIRED_FRAMETIME;
const int MAX_PHYSICS_STEPS = 6;
const float MAX_DELTA_TIME = 1.0f;


const float SCALE_DIVIDER = 1.0f;
const float CAMERA_SCALE = 1.0f / SCALE_DIVIDER;



MainGame::MainGame()
{
	m_screenWidth = 1280;
	m_screenHeight = 960;
	m_player = nullptr;
	m_numHumansKilled = 0;
	m_numZombiesKilled = 0;
	m_gameState = GameState::PLAY;

}

MainGame::~MainGame()
{
	//for no memory leaks since this is pointer
	for (int i = 0; i < m_levels.size(); i++)
	{
		delete m_levels[i];
	}
}

void MainGame::run()
{
	initSystems();
	initLevel();

	m_gameState = GameState::PLAY;
	gameLoop();
}

void MainGame::initSystems()
{
	//first init game engine
	NTCrystal::init();

	//create window
	m_window.create("Zombie game", m_screenWidth, m_screenHeight, NTCrystal::BORDERLESS);
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

	//initilaze shaders on window
	initShaders();

	m_camera.init(m_screenWidth, m_screenHeight);
	m_camera.setScale(CAMERA_SCALE);

	m_hudCamera.init(m_screenWidth, m_screenHeight);
	m_hudCamera.setPosition(glm::vec2(m_screenWidth, m_screenHeight));
	m_hudCamera.setScale(CAMERA_SCALE / 2);

	m_fpsLimiter.init(MAX_FPS);
	m_fpsLimiter.setMaxFPS(60.0f);

	m_ObjectSpriteBatch.init();
	m_hudSpriteBatch.init();

	m_spriteFont = new NTCrystal::SpriteFont("Fonts/zombie.ttf", 64);

	//inits sound must happend after engine init couse SDL_init() is in that init
	m_audioEngine.init();

	//load audio files NOTE: move this to init level for diferent sund for other levels
	//m_currentLevelMusic = m_audioEngine.loadMusic("Sounds/ambience.ogg");

	//init particles
	m_bloodParticleBatch = new NTCrystal::ParticleBatch2D();
	m_bloodParticleBatch->init(1000, 0.05f,
		NTCrystal::ResourceManager::getTexture("Textures/Particles/particle_simple.png"),

		//function withdouth name as refrence
		[/*outside variables */](NTCrystal::Particle2D &particle, float deltaTime){

		particle.position += particle.velocity * deltaTime;
		particle.color.a = (GLubyte)(particle.life * 255.0f);
	});

	m_particleEngine.addParticleBatch(m_bloodParticleBatch);

	m_DefeatSoundEfect = m_audioEngine.loadSoundEffect("Sounds/game/defeat.wav");
	m_VictorySoundEfect = m_audioEngine.loadSoundEffect("Sounds/game/victory.wav");
}

void MainGame::initLevel()
{

	m_levels.push_back(new Level("Levels/BenchMark_level.txt"));
	m_currentLevel = 0;

#if  RELEASE
	m_levels.push_back(new Level("Levels/level1.txt"));
	m_currentLevel = 0;
#endif //  RELEASE

	m_player = new Player();
	m_player->init(PLAYER_SPEED, m_levels[m_currentLevel]->startPlayerPos(), &m_inputManager, &m_camera, &m_bullets);

	m_humans.push_back(m_player);

	std::mt19937 randomEngine;
	randomEngine.seed(time(nullptr));

	std::uniform_real_distribution<float>randX(5, m_levels[m_currentLevel]->getWidth());
	std::uniform_real_distribution<float>randY(5, m_levels[m_currentLevel]->getHeight());

	//add humans
	for (int i = 0; i < m_levels[m_currentLevel]->getNumHumans(); i++)
	{
		m_humans.push_back(new Human);
		glm::vec2 pos(randX(randomEngine) * TILE_WIDTH, randY(randomEngine) * TILE_WIDTH );

		m_humans.back()->init(HUMAN_SPEED, pos);
	}

	//add Zombies
	const std::vector<glm::vec2> &zombiePositions = m_levels[m_currentLevel]->startZombiePos();

	for (int i = 0; i < zombiePositions.size(); i++){
		m_zombies.push_back(new Zombie);
		m_zombies.back()->init(ZOMBIE_SPEED, zombiePositions[i]);
	}

	//give player guns
	const float BULLET_SPEED = 50.0f;
	m_player->addGun(new Gun("Pistol", 20, 1, 0.1f, BULLET_SPEED, 20, &m_audioEngine, "Sounds/shots/pistol.wav"));
	m_player->addGun(new Gun("Shotgun", 60, 5, 0.5f, BULLET_SPEED, 50, &m_audioEngine, "Sounds/shots/shotgun.wav"));
	m_player->addGun(new Gun("MP5", 10, 3, 0.2f, BULLET_SPEED, 10, &m_audioEngine, "Sounds/shots/mp5.wav"));


	std::cout << "Avelable guns: Pistol(1), Shotgun(2), MP5(3)" << std::endl;
}

void MainGame::initShaders()
{
	m_textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	m_textureProgram.addAttribute("vertexPosition");
	m_textureProgram.addAttribute("vertexColor");
	m_textureProgram.addAttribute("vertexUV");
	m_textureProgram.linkShaders();
}

void MainGame::gameLoop()
{
	float previusTicks = SDL_GetTicks();
	bool musicPlaying = false;
	bool levelChange = true;;

	while (m_gameState == GameState::PLAY)
	{
		//set this in update later with loda new level
		if (levelChange == true)
		{
			if (musicPlaying = true)
			{
				//m_currentLevelMusic.stop();
			}
			//if level has changed play difrent music
			//m_currentLevelMusic.play(-1);

			levelChange = false;
			musicPlaying = true;
		}


		m_fpsLimiter.begin();

		float _deltaTime;

		float newTicks = SDL_GetTicks();
		float frameTime = newTicks - previusTicks;
		previusTicks = newTicks;

		float totalDeltaTime = frameTime / DESIRED_FRAMETIME;

		checkVictory();

		m_inputManager.update();

		procesInput();

		int i = 0;

		while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS)
		{
			_deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);

			update(_deltaTime);

			totalDeltaTime -= _deltaTime;

			i++;
		}


		m_camera.setPosition(m_player->getPosition());
		m_camera.update();

		m_hudCamera.update();

		drawGame();

		m_fps = m_fpsLimiter.end();
	}

	if (m_gameState == GameState::VICTORY || m_gameState == GameState::DEFEAT){

		m_playEnd = true;

		glClearColor(0.0f, 0.5f, 0.0f, 1.0f);

		while (m_gameState == GameState::VICTORY || m_gameState == GameState::DEFEAT)
		{

			m_fpsLimiter.begin();

			drawGame();

			m_inputManager.update();

			procesInput();

			m_fps = m_fpsLimiter.end();
		}

	}
}

void MainGame::procesInput()
{
	SDL_Event evnt;

	const float CAMERA_SPEED = 10.0f;
	const float SCALE_SPEED = 0.1f;

	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			m_gameState = GameState::EXIT;
			//eyit game here
			break;
		case SDL_MOUSEMOTION:
			m_inputManager.setMouseCords(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			m_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			m_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			m_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			m_inputManager.releaseKey(evnt.button.button);
			break;
		default:
			break;
		}
	}

	if (m_inputManager.isKeyPressed(SDLK_ESCAPE)){

		if (m_gameState == GameState::VICTORY || m_gameState == GameState::DEFEAT){

			m_gameState = GameState::EXIT;
		}
		else
		{
			m_gameState = GameState::DEFEAT;
		}
	}
}

void MainGame::drawGame()
{
	//clears depth
	glClearDepth(1.0);
	//clear depth and color buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	m_textureProgram.use();

	glActiveTexture(GL_TEXTURE0);

	//get uniform location for shader sampler
	GLint textureLocation = m_textureProgram.getUniformLocation("mySampler");
	//tell shader texture  is in unit 0
	glUniform1i(textureLocation, 0);

	GLuint  pLocation = m_textureProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = m_camera.getCameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	if (m_gameState == GameState::PLAY){
		//draw level
		m_levels[m_currentLevel]->draw();

		//begin drawing agents
		m_ObjectSpriteBatch.begin();

		//change this if agents are diferent dimensions
		const glm::vec2 agentDim(AGENT_RADIUS * 2.0f);

		m_particleEngine.draw(&m_ObjectSpriteBatch);

		//draw humans
		for (int i = 0; i < m_humans.size(); i++)
		{
			if (m_camera.isBoxInView(m_humans[i]->getPosition(), agentDim)){
				m_humans[i]->draw(m_ObjectSpriteBatch);
			}
		}

		//draw zombies
		for (int i = 0; i < m_zombies.size(); i++)
		{
			if (m_camera.isBoxInView(m_zombies[i]->getPosition(), agentDim)){
				m_zombies[i]->draw(m_ObjectSpriteBatch);
			}
		}

		//draw bullets
		for (int i = 0; i < m_bullets.size(); i++)
		{
			if (m_camera.isBoxInView(m_bullets[i].getPosition(), agentDim)){
				m_bullets[i].draw(m_ObjectSpriteBatch);
			}
		}

		m_ObjectSpriteBatch.end();

		m_ObjectSpriteBatch.renderBatch();
	}

	drawHud();

	//glBindTexture(GL_TEXTURE_2D, 0);

	m_textureProgram.unuse();

	//clears window buffer to GPU
	m_window.swapBuffer();
}

void MainGame::drawHud()
{
	//needs to be bigger than we need so we dont overflow it
	char buffer[2048];


	GLuint  pLocation = m_textureProgram.getUniformLocation("P");
	glm::mat4 projectionMatrix = m_hudCamera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(projectionMatrix[0][0]));

	m_hudSpriteBatch.begin();

	if (m_gameState == GameState::PLAY){
		sprintf_s(buffer, "Humans remaining:  %d", m_humans.size() - 1);

		m_spriteFont->draw(m_hudSpriteBatch, buffer, glm::vec2(0, 0),
			glm::vec2(1.0), 0.0f, NTCrystal::ColorRGBA8(255, 100, 100, 255));

		sprintf_s(buffer, "Zombies remaining:  %d", m_zombies.size());

		m_spriteFont->draw(m_hudSpriteBatch, buffer, glm::vec2(0, 150),
			glm::vec2(1.0), 0.0f, NTCrystal::ColorRGBA8(255, 100, 100, 255));

		if (m_player->isGunSelected()){
			sprintf_s(buffer, "Selected wepon:  %s", m_player->getSelectedGun().c_str());

			m_spriteFont->draw(m_hudSpriteBatch, buffer, glm::vec2(1000, 0),
				glm::vec2(1.0), 0.0f, NTCrystal::ColorRGBA8(255, 100, 100, 255));
		}
	}
	else if (m_gameState == GameState::VICTORY || m_gameState == GameState::DEFEAT)
	{
		
		int score = 0;
		if (m_numHumansKilled != 0){
			score = (m_humans.size() * m_numZombiesKilled) / m_numHumansKilled;
		}
		else
		{
			score = (m_humans.size() * m_numZombiesKilled);
		}
		if (m_gameState == GameState::VICTORY){

			if (m_playEnd == true)
			{
				m_VictorySoundEfect.play(0);
				m_playEnd = false;
			}
			sprintf_s(buffer, "Press esc to exit..... \n \n Zombies Killed: %d \n  Humans saved: %d  \n SCORE: %d \n \n YOU WON ",
				m_numZombiesKilled,
				m_humans.size() - 1,
				score);
		}
		else
		{
			if (m_playEnd == true)
			{
				m_DefeatSoundEfect.play(0);
				m_playEnd = false;
			}
			sprintf_s(buffer, "Press esc to exit..... \n \n Zombies Killed: %d \n  Humans saved: %d  \n SCORE: %d \n \n YOU LOSE ",
				m_numZombiesKilled,
				m_humans.size() - 1,
				score);

			glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
		}

		m_hudCamera.setScale(CAMERA_SCALE);
		m_spriteFont->draw(m_hudSpriteBatch, buffer, glm::vec2(m_screenWidth / 2, m_screenHeight / 2),
			glm::vec2(1.0), 0.0f, NTCrystal::ColorRGBA8(0, 100, 100, 255));
	}

	m_hudSpriteBatch.end();
	m_hudSpriteBatch.renderBatch();
}

void MainGame::update(float deltaTime)
{
	updateAgents(deltaTime);
	updateBullets(deltaTime);
	updateParticleEngine(deltaTime);
}

void MainGame::updateAgents(float deltaTime)
{
	//update humans
	for (int i = 0; i < m_humans.size(); i++)
	{
		m_humans[i]->update(m_levels[m_currentLevel]->getLevelData(),
			m_humans,
			m_zombies,
			deltaTime);
	}
	//update zombies
	for (int i = 0; i < m_zombies.size(); i++)
	{
		m_zombies[i]->update(m_levels[m_currentLevel]->getLevelData(),
			m_humans,
			m_zombies,
			deltaTime);
	}

	//update zombie collision
	for (int i = 0; i < m_zombies.size(); i++){
		//collide with zombies
		for (int j = i + 1; j < m_zombies.size(); j++){
			m_zombies[i]->collideWithAgent(m_zombies[j]);
		}
		//collide with humans
		for (int j = 1; j < m_humans.size(); j++){
			if (m_zombies[i]->collideWithAgent(m_humans[j]))
			{
				addBlood(m_humans[j]->getPosition(), 5);

				//add new zombie
				m_zombies.push_back(new Zombie);
				m_zombies.back()->init(ZOMBIE_SPEED, m_humans[j]->getPosition());

				delete m_humans[j];
				m_humans[j] = m_humans.back();
				m_humans.pop_back();

			}
		}
		if (m_zombies[i]->collideWithAgent(m_player)){

			addBlood(m_humans[0]->getPosition(), 5);
			
			if (m_player->applyDamage(10.0f))
			{
				m_gameState = GameState::DEFEAT;
			}
		}
	}

	//update Human collisons
	for (int i = 0; i < m_humans.size(); i++){
		//collide with other humans
		for (int j = i + 1; j < m_humans.size(); j++){
			m_humans[i]->collideWithAgent(m_humans[j]);
		}
	}
}

void MainGame::updateBullets(float deltaTime)
{
	//update all bullets
	for (int i = 0; i < m_bullets.size();)
	{
		//if update true bullet collide with wall
		if (m_bullets[i].update(m_levels[m_currentLevel]->getLevelData(), deltaTime))
		{
			m_bullets[i] = m_bullets.back();
			m_bullets.pop_back();
		}
		else
		{
			i++;
		}
	}

	bool wasBulletRemoved;

	for (int i = 0; i < m_bullets.size(); i++) {
		wasBulletRemoved = false;
		// Loop through zombies
		for (int j = 0; j < m_zombies.size();) {
			// Check collision
			if (m_bullets[i].collideWithAgent(m_zombies[j])) {
				addBlood(m_bullets[i].getPosition(), 5);
				// Damage zombie, and kill it if its out of health
				if (m_zombies[j]->applyDamage(m_bullets[i].getDamage())) {
					// If the zombie died, remove him
					delete m_zombies[j];
					m_zombies[j] = m_zombies.back();
					m_zombies.pop_back();
					m_numZombiesKilled++;
				}

				else {
					j++;
				}

				// Remove the bullet
				m_bullets[i] = m_bullets.back();
				m_bullets.pop_back();
				wasBulletRemoved = true;
				i--; // Make sure we don't skip a bullet
				break;
			}
			else {
				j++;
			}
		}
		// Loop through humans
		if (wasBulletRemoved == false) {
			for (int j = 1; j < m_humans.size();) {
				// Check collision
				if (m_bullets[i].collideWithAgent(m_humans[j])) {
					addBlood(m_bullets[i].getPosition(), 5);
					// Damage human, and kill it if its out of health
					if (m_humans[j]->applyDamage(m_bullets[i].getDamage())) {
						// If the human died, remove him
						delete m_humans[j];
						m_humans[j] = m_humans.back();
						m_humans.pop_back();
						m_numHumansKilled++;
					}
					else {
						j++;
					}

					// Remove the bullet
					m_bullets[i] = m_bullets.back();
					m_bullets.pop_back();

					i--; // Make sure we don't skip a bullet

					break;
				}
				else {
					j++;
				}
			}
		}
	}
}

void MainGame::checkVictory()
{
	if (m_zombies.size() == 0)
	{
		m_gameState = GameState::VICTORY;
	}
}

void MainGame::loadNewLevel()
{
	//TO DO
}

void MainGame::updateParticleEngine(float deltaTime)
{
	m_particleEngine.update(deltaTime);
}

void MainGame::addBlood(const glm::vec2 &position, int numParticles)
{
	static std::mt19937 randEngine(time(nullptr));
	static std::uniform_real_distribution<float> randAngle(0.0f, 360.0f);


	glm::vec2 vel(2.0f, 0.0f);

	for (int i = 0; i < numParticles; i++)
	{
		m_bloodParticleBatch->addParticle(position, glm::rotate(vel, randAngle(randEngine)),
			NTCrystal::ColorRGBA8(255, 0, 0, 255), 8.0f);
	}

}

