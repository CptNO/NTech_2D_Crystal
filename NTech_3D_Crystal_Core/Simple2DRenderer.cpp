#include "Simple2DRenderer.h"

namespace NTCrystal{
	namespace Graphics{

		void Simple2DRenderer::submit(const Renderable2D *renderable)
		{
			m_renderQueue.push_back((StaticSprite*)renderable);
		}

		void Simple2DRenderer::flush()
		{
			while (!m_renderQueue.empty())
			{
				StaticSprite* sprite = m_renderQueue.front();
				sprite->getVAO()->bind();
				sprite->getIBO()->bind();

				sprite->getShader().setUniformMat4("ml_matrix", math::mat4::Translate(sprite->getPosition()));
				glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

				sprite->getIBO()->unbind();
				sprite->getVAO()->unbind();

				m_renderQueue.pop_front();

			}
		}

	}
}