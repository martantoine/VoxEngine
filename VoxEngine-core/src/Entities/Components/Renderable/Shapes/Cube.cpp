#include "Cube.h"

namespace VoxEngine
{
	namespace VEEntity
	{
		//--------------------------------------------------------------------------------//
		//**********************************Constructors**********************************//
		//--------------------------------------------------------------------------------//
		Cube::Cube()
		{
			m_EntityComponentType = EntityComponentType::Graphic;

			m_Size = glm::vec3(1.0f, 1.0f, 1.0f);
			m_Color = glm::vec3(0.4f, 0.4f, 0.4f);
			m_Textured = false;

			m_lScale = glm::mat4(1.0f);
			m_lRotation = glm::mat4(1.0f);
			m_lTranslation = glm::mat4(1.0f);

			m_Vertices = new VertexData[8];
			m_Indices = new GLushort[36];
			m_Normal = new glm::vec3[8];

			m_VAO = new Graphics::VAO();
			InitGeometry();
			m_EBO = new Graphics::EBO(m_Indices, 36);
		}

		Cube::Cube(glm::vec3 position, glm::vec3 size, float angle, glm::vec3 axis, glm::vec3 colors)
		{
			m_EntityComponentType = EntityComponentType::Graphic;

			m_Size = size;
			m_Color = colors;
			m_Textured = false;
			m_Vertices = new VertexData[8];
			m_Indices = new GLushort[36];
			m_Normal = new glm::vec3[8];

			m_lTranslation = glm::translate(glm::mat4(1.0f), position);
			m_lScale = glm::mat4(1.0f);
			m_lRotation = glm::rotate(glm::mat4(1.0f), glm::radians(-angle), axis);

			m_VAO = new Graphics::VAO();
			InitGeometry();
			m_EBO = new Graphics::EBO(m_Indices, 36);
		}



		//-------------------------------------------------------------------------------//
		//**************************EntityComponent's function***************************//
		//-------------------------------------------------------------------------------//
		void Cube::InitGeometry()
		{
			///Initial vertex's position
			m_Vertices[0].vertice = glm::vec3(0.0f, 0.0f, 0.0f);
			m_Vertices[1].vertice = glm::vec3(m_Size.x, 0.0f, 0.0f);
			m_Vertices[2].vertice = glm::vec3(m_Size.x, m_Size.y, 0.0f);
			m_Vertices[3].vertice = glm::vec3(0.0f, m_Size.y, 0.0f);
			m_Vertices[4].vertice = glm::vec3(0.0f, 0.0f, m_Size.z);
			m_Vertices[5].vertice = glm::vec3(m_Size.x, 0.0f, m_Size.z);
			m_Vertices[6].vertice = glm::vec3(m_Size.x, m_Size.y, m_Size.z);
			m_Vertices[7].vertice = glm::vec3(0.0f, m_Size.y, m_Size.z);

			///Set vertex's normal
			m_Vertices[0].normal = glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f);
			m_Vertices[1].normal = glm::vec4(1.0f,  -1.0f, -1.0f, 1.0f);
			m_Vertices[2].normal = glm::vec4(1.0f,   1.0f, -1.0f, 1.0f);
			m_Vertices[3].normal = glm::vec4(-1.0f,  1.0f, -1.0f, 1.0f);
			m_Vertices[4].normal = glm::vec4(-1.0f, -1.0f,  1.0f, 1.0f);
			m_Vertices[5].normal = glm::vec4(1.0f,  -1.0f,  1.0f, 1.0f);
			m_Vertices[6].normal = glm::vec4(1.0f,   1.0f,  1.0f, 1.0f);
			m_Vertices[7].normal = glm::vec4(-1.0f,  1.0f,  1.0f, 1.0f);

			///Set vertex's color
			m_Vertices[0].color = m_Color;
			m_Vertices[1].color = m_Color;
			m_Vertices[2].color = m_Color;
			m_Vertices[3].color = m_Color;
			m_Vertices[4].color = m_Color;
			m_Vertices[5].color = m_Color;
			m_Vertices[6].color = m_Color;
			m_Vertices[7].color = m_Color;
			
			///Set indices
			//Face bottom
			m_Indices[0] = 0;
			m_Indices[1] = 1;
			m_Indices[2] = 2;
			m_Indices[3] = 2;
			m_Indices[4] = 3;
			m_Indices[5] = 0;

			//Face top
			m_Indices[6] = 6;
			m_Indices[7] = 5;
			m_Indices[8] = 4;
			m_Indices[9] = 4;
			m_Indices[10] = 7;
			m_Indices[11] = 6;

			//Face right
			m_Indices[12] = 1;
			m_Indices[13] = 2;
			m_Indices[14] = 6;
			m_Indices[15] = 6;
			m_Indices[16] = 5;
			m_Indices[17] = 1;

			//Face left
			m_Indices[18] = 0;
			m_Indices[19] = 3;
			m_Indices[20] = 7;
			m_Indices[21] = 7;
			m_Indices[22] = 4;
			m_Indices[23] = 0;

			//Face front
			m_Indices[24] = 0;
			m_Indices[25] = 1;
			m_Indices[26] = 5;
			m_Indices[27] = 5;
			m_Indices[28] = 4;
			m_Indices[29] = 0;

			//Face back
			m_Indices[30] = 3;
			m_Indices[31] = 2;
			m_Indices[32] = 6;
			m_Indices[33] = 6;
			m_Indices[34] = 7;
			m_Indices[35] = 3;

			Graphics::VBO* vbo = new Graphics::VBO(&m_Vertices->vertice, 8, 4);

			m_VAO->ClearVBO();
			m_VAO->AddVBO(vbo, 0, VERTEX);
			m_VAO->AddVBO(vbo, 1, NORMAL);
			m_VAO->AddVBO(vbo, 2, COLOR);
			if (m_Textured)
				m_VAO->AddVBO(vbo, 3, TEXTURE);
		}

		void Cube::AddTexture(Graphics::MATERIAL_TEXTURE type)
		{
			m_Textured = true;
			glm::vec2 positionFloat;

			if (type == Graphics::MATERIAL_TEXTURE::DIFFUSE)
				positionFloat = glm::vec2(0.0f / m_Material->diffuse->GetWidth(), 0.0f / m_Material->diffuse->GetHeight());
			else if (type == Graphics::MATERIAL_TEXTURE::SPECULAR)
				positionFloat = glm::vec2(0.0f / m_Material->specular->GetWidth(), 0.0f / m_Material->specular->GetHeight());

			m_Vertices[0].texCoord = positionFloat + glm::vec2(0.0f, 1.0f);
			m_Vertices[1].texCoord = positionFloat + glm::vec2(1.0f, 1.0f);
			m_Vertices[2].texCoord = positionFloat + glm::vec2(1.0f, 0.0f);
			m_Vertices[3].texCoord = positionFloat;
			m_Vertices[4].texCoord = positionFloat + glm::vec2(1.0f, 0.0f);
			m_Vertices[5].texCoord = positionFloat + glm::vec2(0.0f, 1.0f);
			m_Vertices[6].texCoord = positionFloat + glm::vec2(1.0f, 1.0f);
			m_Vertices[7].texCoord = positionFloat;

			InitGeometry();
		}

	}
}