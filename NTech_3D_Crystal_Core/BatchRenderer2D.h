#pragma once
#include "Renderer2D.h"

namespace NTCrystal{
	namespace Graphics
	{

#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDECIES_SIZE	RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX		0
#define SHADER_COLOR_INDEX		1

		class BatchRenderer2D : public Renderer2D
		{
		private:
			IndexBuffer* m_ibo;
			GLsizei	m_indexCount;
			GLuint m_vao;
			GLuint m_vbo;
			VertexData* m_buffer;
			void init();
			
		public:
			BatchRenderer2D();
			~BatchRenderer2D(); 

			void begin();
			void submit(const Renderable2D *renderable) override;
			void end();
			void flush() override;

		};
	}
}

