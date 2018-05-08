#include "VBO.h"

namespace UE
{
	namespace UEGraphics
	{

		//--------------------------------------------------------------------------------//
		//**********************************Constructors**********************************//
		//--------------------------------------------------------------------------------//
		VBO::VBO(glm::vec3* data, int count, GLuint componentCount)
			: m_ComponentCount(componentCount)
		{
			glGenBuffers(1, &m_VBO);
			Bind();
			glBufferData(GL_ARRAY_BUFFER, count * sizeof(VertexData), data, GL_STATIC_DRAW);
			Unbind();
		}

		VBO::VBO(std::vector<glm::vec3> data, int count, GLuint componentCount)
			: m_ComponentCount(componentCount)
		{
			glGenBuffers(1, &m_VBO);
			Bind();
			glBufferData(GL_ARRAY_BUFFER, count * sizeof(VertexData), data.data(), GL_STATIC_DRAW);
			Unbind();
		}



		//--------------------------------------------------------------------------------//
		//*************************************Miscs**************************************//
		//--------------------------------------------------------------------------------//
		void VBO::Bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		}

		void VBO::Unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		GLuint VBO::GetComponentCount()
		{
			return m_ComponentCount;
		}


		
		//--------------------------------------------------------------------------------//
		//***********************************Destructor***********************************//
		//--------------------------------------------------------------------------------//
		void VBO::Destroy()
		{
			glDeleteBuffers(1, &m_VBO);
		}

		VBO::~VBO()
		{
			Destroy();
		}

	}
}