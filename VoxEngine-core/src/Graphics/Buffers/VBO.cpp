#include "VBO.h"

namespace VoxEngine {
	namespace Graphics {

		VBO::VBO(glm::vec3* data, int count, GLuint componentCount)
			: m_ComponentCount(componentCount)
		{
			glGenBuffers(1, &m_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, count * sizeof(VertexData), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		VBO::VBO(std::vector<glm::vec3> data, int count, GLuint componentCount)
			: m_ComponentCount(componentCount)
		{
			glGenBuffers(1, &m_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, count * sizeof(VertexData), &data[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void VBO::Bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		}

		void VBO::Unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

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