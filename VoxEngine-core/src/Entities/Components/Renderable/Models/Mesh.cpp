#include "Mesh.h"

namespace VoxEngine
{
	namespace VEEntity
	{
		//--------------------------------------------------------------------------------//
		//**********************************Constructors**********************************//
		//--------------------------------------------------------------------------------//
		Mesh::Mesh(std::vector<VertexData> vertices, std::vector<GLuint> indices)
		{
			m_Vertices = vertices;
			m_Indices = indices;

			SetupMesh();
		}



		//--------------------------------------------------------------------------------//
		//********************************Mesh's functions********************************//
		//--------------------------------------------------------------------------------//
		void Mesh::SetupMesh()
		{
			m_VAO = new Graphics::VAO();

			Graphics::VBO* vbo = new Graphics::VBO(&m_Vertices[0].vertice, m_Vertices.size(), 4);

			m_VAO->ClearVBO();
			m_VAO->AddVBO(vbo, 0, VERTEX);
			m_VAO->AddVBO(vbo, 1, NORMAL);
			m_VAO->AddVBO(vbo, 2, COLOR);
			if (m_Textured)
				m_VAO->AddVBO(vbo, 3, TEXTURE);

			m_EBO = new Graphics::EBO(m_Indices, m_Indices.size());
		}
	}
}