#pragma once
#include "Renderable2D.h"

namespace NTCrystal{
	namespace Graphics{

		class Sprite : public Renderable2D 
		{
		public:
			Sprite(math::vec3 position, math::vec2 size, math::vec4 &color);
		};
	}
}

