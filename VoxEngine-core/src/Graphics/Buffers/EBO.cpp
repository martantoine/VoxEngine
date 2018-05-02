#include "EBO.h"

namespace VoxEngine {
	namespace Graphics {

		EBO::EBO(GLushort* data, int count)
			: m_Count(count)
		{
			glGenBuffers(1, &m_EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		EBO::EBO(std::vector<GLuint> data, int count)
			: m_Count(count)
		{
			glGenBuffers(1, &m_EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), &data[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void EBO::Bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		}

		void EBO::Unbind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void EBO::Destroy()
		{
			glDeleteBuffers(1, &m_EBO);
		}

		EBO::~EBO()
		{
			Destroy();
		}

	}
}