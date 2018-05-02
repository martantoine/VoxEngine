#include "VAO.h"

namespace VoxEngine {
	namespace Graphics {

		VAO::VAO()
		{
			glGenVertexArrays(1, &m_VAO);
		}

		void VAO::AddVBO(VBO* vbo, GLuint index, vertexDataVar var)
		{
			Bind();
			vbo->Bind();

			if (var == COLOR)
				glVertexAttribPointer(index, vbo->GetComponentCount(), GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(offsetof(VertexData, VertexData::color)));
			else if (var == VERTEX)
				glVertexAttribPointer(index, vbo->GetComponentCount(), GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(offsetof(VertexData, VertexData::vertice)));
			else if (var == TEXTURE)
				glVertexAttribPointer(index, vbo->GetComponentCount(), GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(offsetof(VertexData, VertexData::texCoord)));
			else if (var == NORMAL)
				glVertexAttribPointer(index, vbo->GetComponentCount(), GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(offsetof(VertexData, VertexData::normal)));
			
			glEnableVertexAttribArray(index);

			vbo->Unbind();
			Unbind();

			m_VBOs.push_back(vbo);
		}

		void VAO::Bind() const
		{
			glBindVertexArray(m_VAO);
		}

		void VAO::Unbind() const
		{
			glBindVertexArray(0);
		}

		void VAO::Destroy()
		{
			glDeleteVertexArrays(1, &m_VAO);
		}

		VAO::~VAO()
		{
			Destroy();
		}

	}
}