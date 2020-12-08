#pragma once
#include <glew.h>
#include <vector>

#include "Buffer.h"

namespace NTCrystal{
	namespace Graphics{

		class VertexArray
		{
		public:
			VertexArray();
			~VertexArray();

			void addBuffer(Buffer *buffer, GLuint index);
			void bind() const;
			void unbind() const;
		private:
			GLuint m_arrayID;
			std::vector<Buffer*> m_buffers;
		};
	}
}

