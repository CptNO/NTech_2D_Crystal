#include "ParticleEngine2D.h"

namespace NTCrystal{

	ParticleEngine2D::ParticleEngine2D()
	{
		//Empty
	}


	ParticleEngine2D::~ParticleEngine2D()
	{
		for each (auto &b in m_batches){
			delete  b;
		}
	}

	void ParticleEngine2D::addParticleBatch(ParticleBatch2D *particleBatch)
	{
		m_batches.push_back(particleBatch);
	}

	void ParticleEngine2D::update(float deltaTime)
	{
		for each (auto &b in m_batches)
		{
			b->update(deltaTime);
		}
	}

	void ParticleEngine2D::draw(SpriteBatch *spriteBatch)
	{

		for each ( auto &b in m_batches)
		{
			spriteBatch->begin();

			b->draw(spriteBatch);

			spriteBatch->end();
			spriteBatch->renderBatch();
		}
	}

}