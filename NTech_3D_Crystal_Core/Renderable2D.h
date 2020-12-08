#pragma once
#include "maths.h"
#include "Buffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

namespace NTCrystal{
	namespace Graphics{
		struct VertexData
		{
			math::vec3 vertex;
			math::vec4 color;
		};
		class Renderable2D
		{
		public:
			Renderable2D(math::vec3 position, math::vec2 size, math::vec4 color) :
				m_position(position), m_color(color), m_size(size){}

			virtual ~Renderable2D(){ /*Empty*/ }

			inline const math::vec3 &getPosition() const { return m_position; }
			inline const math::vec2 &getSize() const { return m_size; }
			inline const math::vec4 &getColor() const { return m_color; }

		protected:
			math::vec2 m_size;
			math::vec3 m_position;
			math::vec4 m_color;

		};

		
	}
}