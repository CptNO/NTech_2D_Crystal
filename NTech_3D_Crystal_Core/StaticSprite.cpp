#include "StaticSprite.h"
namespace NTCrystal{
	namespace Graphics{

		StaticSprite::StaticSprite(math::vec3 position, math::vec2 size, math::vec4 &color, Shader &shader)
			: Renderable2D(position, size, color), m_shader(shader)
		{
			m_vertexArray = new VertexArray();
			GLfloat vertecies[] =
			{
				0, 0, 0,
				0, size.x, 0,
				size.x, size.y, 0,
				size.x, 0, 0
			};

			GLfloat colors[] =
			{
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w
			};
			m_vertexArray->addBuffer(new Buffer(vertecies, 4 * 3, 3), 0);
			m_vertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

			GLushort indecies[] = { 0, 1, 2, 2, 3, 0 };
			m_indexBuffer = new IndexBuffer(indecies, 6);
		}


		StaticSprite::~StaticSprite()
		{

		}
	}
}
