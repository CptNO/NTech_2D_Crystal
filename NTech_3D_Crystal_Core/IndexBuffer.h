#pragma once
#include <glew.h>

namespace NTCrystal{
	namespace Graphics{
		class IndexBuffer
		{
		public:
			IndexBuffer(GLushort *data, GLsizei count);
			~IndexBuffer();

			void bind() const;
			void unbind() const;
			GLuint getCount() const { return m_count; }

		private:
			GLuint m_bufferID;
			GLuint m_count;

			void init(GLushort *data, GLsizei count);
		};

	}
}