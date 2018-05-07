#include "EBO.h"

namespace VoxEngine
{
	namespace VEGraphics
	{

		//--------------------------------------------------------------------------------//
		//**********************************Constructors**********************************//
		//--------------------------------------------------------------------------------//
		EBO::EBO()
		{
		}

		EBO::EBO(GLuint* data, int count)
		{
			CreateEBO(data, count);
		}



		//--------------------------------------------------------------------------------//
		//**********************************Initializer***********************************//
		//--------------------------------------------------------------------------------//
		void EBO::CreateEBO(GLuint* data, int count)
		{
			m_Count = count;
			
			glGenBuffers(1, &m_EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(GLuint), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		


		//--------------------------------------------------------------------------------//
		//*************************************Miscs**************************************//
		//--------------------------------------------------------------------------------//
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



		//--------------------------------------------------------------------------------//
		//***********************************Destructor***********************************//
		//--------------------------------------------------------------------------------//
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