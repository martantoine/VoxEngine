#include "EBO.h"

namespace VoxEngine
{
	namespace Graphics
	{
		EBO::EBO()
		{
		}

		EBO::EBO(GLuint* data, int count)
		{
			CreateEBO(data, count);
		}

		void EBO::CreateEBO(GLuint* data, int count)
		{
			m_Count = count;
			
			glGenBuffers(1, &m_EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(GLuint), data, GL_STATIC_DRAW);
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

		GLuint EBO::GetCount() const
		{
			return m_Count;
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