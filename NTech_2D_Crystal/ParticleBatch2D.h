#pragma once

#include <glm/glm.hpp>
#include "Vertex.h"
#include "SpriteBatch.h"
#include "GLTexture.h"
#include <functional>

namespace NTCrystal{

	class Particle2D
	{
	public:
		glm::vec2 position = glm::vec2(0.0f);
		glm::vec2 velocity = glm::vec2(0.0f);

		ColorRGBA8 color;

		float life = 1.0f;
		float width = 0.0f;
	};

	inline void defaultParticleUpdate(Particle2D& particle, float deltaTime)
	{
		particle.position += particle.velocity * deltaTime;
	}


	class ParticleBatch2D
	{
	public:

		ParticleBatch2D();
		~ParticleBatch2D();

		//Default particle update is default particle update function if not changed
		void init(int maxParticles, float decayRate, 
			GLTexture texture, 
			std::function<void(Particle2D&, float)> updateFunc = defaultParticleUpdate);

		void addParticle(const glm::vec2 &position, 
			const glm::vec2 &velocity,
			const ColorRGBA8 &color,
			float width);

		void update(float deltaTime);

		void draw(SpriteBatch *spriteBatch);


	private:

		int findFreeParticle();


		std::function<void(Particle2D&, float)> m_updateFunc;
		float m_decayRate = 0.1f;
		Particle2D *m_particles = nullptr;

		int m_lastFreeParticle = 0;
		int m_maxParticles = 0;

		GLTexture m_texture;


	};

}