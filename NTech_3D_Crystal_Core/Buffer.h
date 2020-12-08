#pragma once
#include <glew.h>

namespace NTCrystal{
	namespace Graphics{
		class Buffer
		{
		public:
			Buffer(GLfloat *data, GLsizei count, GLuint componentCount);
			~Buffer();
			
			void bind() const;
			void unbind() const;
			GLuint getComponentCount() const { return m_componentCount; }
			
		private:
			GLuint m_bufferID;
			GLuint m_componentCount;

			void init(GLfloat *data, GLsizei count);
		};

	}
}