#pragma once
#include "Renderable2D.h"
#include "Shader.h"


namespace NTCrystal{
	namespace Graphics{

		class StaticSprite : public Renderable2D
		{
		public:
			StaticSprite(math::vec3 position, math::vec2 size, math::vec4 &color, Shader &shader);
			~StaticSprite();

			inline const VertexArray* getVAO() { return m_vertexArray; }
			inline const IndexBuffer* getIBO() { return m_indexBuffer; }
			inline Shader &getShader(){ return m_shader; }
		private:
			VertexArray* m_vertexArray;
			IndexBuffer* m_indexBuffer;
			Shader &m_shader;
		};

	}
}