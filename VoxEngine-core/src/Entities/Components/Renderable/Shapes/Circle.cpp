#include "Circle.h"

namespace VoxEngine {
	namespace Graphics {

		Circle::Circle(glm::vec3 position, float radius, float verticesNbr)
		{
			GLuint indicesNbr = 3 * verticesNbr;
			m_Position = position;
			m_VerticesNbr = verticesNbr;
			m_Radius = radius;
			m_Angle = (2 * M_PI) / m_VerticesNbr;

			m_Vertices = new VertexData[verticesNbr + 1];
			m_Indices = new GLushort[indicesNbr];
			
			float currentAngle = 0.0f;
			for (int i(0); i < m_VerticesNbr; i++)
			{
				m_Vertices[i].vertice = m_Position + glm::vec3(cos(currentAngle) * m_Radius, sin(currentAngle) * m_Radius, 0);
				m_Vertices[i].color = glm::vec3(0.1f, 0.2f, 0.6f);
				currentAngle += m_Angle;
			}
			for (int i(0); i < m_VerticesNbr; i++)
			{
				m_Indices[ i  *  3 ] = 0;
				m_Indices[i * 3 + 1] = i + 1;
				m_Indices[i * 3 + 2] = i + 2;
				if (m_Indices[i * 3 + 2] == m_VerticesNbr)
					m_Indices[i * 3 + 2] = 1;
			}

			m_VAO = new VAO();
			VBO* vbo = new VBO(&m_Vertices->vertice, verticesNbr * 2, 4);
		
			m_VAO->AddVBO(vbo, 0, VERTEX);
			m_VAO->AddVBO(vbo, 1, NORMAL);
			m_VAO->AddVBO(vbo, 2, COLOR);
			if (m_Textured)
				m_VAO->AddVBO(vbo, 3, TEXTURE);

			m_EBO = new EBO(m_Indices, indicesNbr);
		}


		void Circle::UpdateShape()
		{

		}

	}
}