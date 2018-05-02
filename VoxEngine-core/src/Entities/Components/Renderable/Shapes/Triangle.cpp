#include "Triangle.h"

namespace VoxEngine {
	namespace Graphics {

		Triangle::Triangle(glm::vec3 position, glm::vec3 side1, glm::vec3 side2)
		{
			m_Position = position;
			m_Vertices = new VertexData[3];
			m_Indices = new GLushort[3];

			m_Vertices[0].vertice = position;
			m_Vertices[1].vertice = position + glm::vec3(side1.x, side1.y, side1.z);
			m_Vertices[2].vertice = position + glm::vec3(side2.x + side1.x, side2.y + side1.y, side1.z + side2.z);

			m_Vertices[0].color = glm::vec3(0.5f, 0.0f, 0.0f);
			m_Vertices[1].color = glm::vec3(0.0f, 0.5f, 0.0f);
			m_Vertices[2].color = glm::vec3(0.0f, 0.0f, 0.5f);

			m_Indices[0] = 0;
			m_Indices[1] = 1;
			m_Indices[2] = 2;


			m_VAO = new VAO();
			VBO* vbo = new VBO(&m_Vertices->vertice, 3 * 2, 4);

			m_VAO->AddVBO(vbo, 0, VERTEX);
			m_VAO->AddVBO(vbo, 1, NORMAL);
			m_VAO->AddVBO(vbo, 2, COLOR);
			if (m_Textured)
				m_VAO->AddVBO(vbo, 3, TEXTURE);

			m_EBO = new EBO(m_Indices, 3);
		}

		void Triangle::UpdateShape()
		{

		}

	}
}