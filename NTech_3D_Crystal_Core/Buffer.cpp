#include "Buffer.h"

namespace NTCrystal{
	namespace Graphics{

		Buffer::Buffer(GLfloat *data, GLsizei count, GLuint componentCount) :
			m_componentCount(componentCount)
		{
			init(data, count);
		}

		Buffer::~Buffer()
		{
			glDeleteBuffers(1, &m_bufferID);
		}

		void Buffer::init(GLfloat *data, GLsizei count)
		{
			glGenBuffers(1, &m_bufferID);
			glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
			glBufferData(GL_ARRAY_BUFFER, count *sizeof(GLfloat), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void Buffer::bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
		}

		void Buffer::unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

	}
}