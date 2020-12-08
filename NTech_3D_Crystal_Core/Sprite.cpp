#include "Sprite.h"

namespace NTCrystal{
	namespace Graphics{
		Sprite::Sprite(math::vec3 position, math::vec2 size, math::vec4 &color)
			: Renderable2D(position, size, color)
		{

		}
	}
}
