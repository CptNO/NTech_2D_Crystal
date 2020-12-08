#include "BatchRenderer2D.h"

namespace NTCrystal{
	namespace Graphics{

		BatchRenderer2D::BatchRenderer2D()
		{
			init();
		}


		BatchRenderer2D::~BatchRenderer2D()
		{
			delete m_ibo;
			glDeleteBuffers(1, &m_vbo);

		}

		void BatchRenderer2D::init()
		{
			glGenVertexArrays(1, &m_vao);
			glGenBuffers(1, &m_vbo);
			glBindVertexArray(m_vao);

			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);
			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, ((const GLvoid*)0));
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, ((const GLvoid*)(3 * sizeof(GLfloat))));
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLushort indecies[RENDERER_INDECIES_SIZE];
			int offset = 0;
			for (int i = 0; i < RENDERER_INDECIES_SIZE; i += 6)
			{
				indecies[  i  ] = offset + 0;
				indecies[i + 1] = offset + 1;
				indecies[i + 2] = offset + 2;

				indecies[i + 3] = offset + 2;
				indecies[i + 4] = offset + 3;
				indecies[i + 5] = offset + 0;

				offset += 4;
			}
			m_ibo = new IndexBuffer(indecies, RENDERER_INDECIES_SIZE);
			glBindVertexArray(0); 
		}


		void BatchRenderer2D::begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			m_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void BatchRenderer2D::submit(const Renderable2D *renderable)
		{
			const math::vec3 &position = renderable->getPosition();
			const math::vec2 &size = renderable->getSize();
			const math::vec4 &color = renderable->getColor();

			m_buffer->vertex = position;
			m_buffer->color = color;
			m_buffer++;

			m_buffer->vertex = math::vec3(position.x, position.y + size.y, position.z);
			m_buffer->color = color;
			m_buffer++;

			m_buffer->vertex = math::vec3(position.x + size.x, position.y + size.y, position.z);
			m_buffer->color = color;
			m_buffer++;

			m_buffer->vertex = math::vec3(position.x + size.x, position.y, position.z);
			m_buffer->color = color;
			m_buffer++;

			m_indexCount += 6;
		}

		void BatchRenderer2D::end()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void BatchRenderer2D::flush()
		{
			glBindVertexArray(m_vao);
			m_ibo->bind();
			glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, NULL);
			m_ibo->bind();
			glBindVertexArray(0);

			m_indexCount = 0;
		}

	}
}
