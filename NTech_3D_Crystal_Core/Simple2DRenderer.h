#pragma once

#include "Renderable2D.h"
#include "Renderer2D.h"
#include "StaticSprite.h"
#include "maths.h"
#include <glew.h>
#include <deque>

namespace NTCrystal{
	namespace Graphics{
		class Simple2DRenderer : public Renderer2D
		{
/*		public:
			Simple2DRenderer();
			~Simple2DRenderer();
*/
		public:
			void submit(const Renderable2D *renderable) override;
			void flush() override;
		private:
			std::deque<StaticSprite*>	m_renderQueue;

		};
	}
}
