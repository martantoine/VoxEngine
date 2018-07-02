#include "Rectangle.h"

namespace UE
{
	namespace UEntity
	{

		//--------------------------------------------------------------------------------//
		//**********************************Constructors**********************************//
		//--------------------------------------------------------------------------------//
		Rectangle::Rectangle()
		{
			m_EntityComponentType = EntityComponentType::GRAPHIC2D;

			m_Size = glm::vec2(1.0f, 1.0f);

			m_Textured = false;
			m_Vertices = new VertexData[4];
			m_Indices = new GLushort[6];

			m_lScale = glm::mat4(1.0f);
			m_lRotation = glm::mat4(1.0f);
			m_lTranslation = glm::mat4(1.0f);

			m_VAO = new UEGraphics::VAO();
			InitGeometry();
			m_EBO = new UEGraphics::EBO(m_Indices, 6);
		}

		Rectangle::Rectangle(glm::vec3 position, glm::vec2 size, float angle, glm::vec3 axis, glm::vec3 color)
		{
			m_EntityComponentType = EntityComponentType::GRAPHIC2D;

			m_Size = size;

			m_Textured = false;
			m_Vertices = new VertexData[4];
			m_Indices = new GLushort[6];

			m_lTranslation = glm::translate(glm::mat4(1.0f), position);
			m_lScale = glm::mat4(1.0f);
			m_lRotation = glm::rotate(glm::mat4(1.0f), glm::radians(-angle), axis);

			m_VAO = new UEGraphics::VAO();
			InitGeometry();
			m_EBO = new UEGraphics::EBO(m_Indices, 6);
		}
		


		//-------------------------------------------------------------------------------//
		//**************************EntityComponent's function***************************//
		//-------------------------------------------------------------------------------//
		void Rectangle::SetParameters(glm::vec3 position, glm::vec2 size, float angle, glm::vec3 axis, glm::vec3 color)
		{
			m_lTranslation = glm::translate(glm::mat4(1.0f), position);
			m_lScale = glm::mat4(1.0f);
			m_lRotation = glm::rotate(glm::mat4(1.0f), glm::radians(-angle), axis);
			m_Size = size;

			InitGeometry();
		}
		
		
		void Rectangle::InitGeometry(const char* modelPath)
		{
			///Initial vertex's position
			m_Vertices[0].vertice = glm::vec3(0.0f, m_Size.y, 0.0f);
			m_Vertices[1].vertice = glm::vec3(m_Size.x, m_Size.y, 0.0f);
			m_Vertices[2].vertice = glm::vec3(m_Size.x, 0.0f, 0.0f);
			m_Vertices[3].vertice = glm::vec3(0.0f, 0.0f, 0.0f);

			///Set vertex's normal
			m_Vertices[0].normal = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
			m_Vertices[1].normal = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
			m_Vertices[2].normal = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
			m_Vertices[3].normal = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);

			///Set vertex's color
			m_Vertices[0].color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			m_Vertices[1].color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			m_Vertices[2].color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			m_Vertices[3].color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

			///Set indices
			m_Indices[0] = 0;
			m_Indices[1] = 3;
			m_Indices[2] = 2;
			m_Indices[3] = 2;
			m_Indices[4] = 1;
			m_Indices[5] = 0;

			///Send data to buffers
			UEGraphics::VBO* vbo = new UEGraphics::VBO(&m_Vertices->vertice, 4, 4);
			m_VAO->ClearVBO();
			m_VAO->AddVBO(vbo, 0, VERTEX);
			m_VAO->AddVBO(vbo, 1, NORMAL);
			m_VAO->AddVBO(vbo, 2, COLOR);
			if (m_Textured)
				m_VAO->AddVBO(vbo, 3, TEXTURE);
		}
		


		//-------------------------------------------------------------------------------//
		//************************************Texture************************************//
		//-------------------------------------------------------------------------------//
		void Rectangle::SetTextures()
		{
			AddTexture(UEGraphics::MATERIAL_TEXTURE::DIFFUSE);
		}
		
		void Rectangle::AddTexture(UEGraphics::MATERIAL_TEXTURE type)
		{
			m_Textured = true;
			glm::vec2 positionFloat(0.0f, 0.0f);

			m_Vertices[0].texCoord = positionFloat;
			m_Vertices[1].texCoord = positionFloat + glm::vec2(1.0f, 0.0f);
			m_Vertices[2].texCoord = positionFloat + glm::vec2(1.0f, 1.0f);
			m_Vertices[3].texCoord = positionFloat + glm::vec2(0.0f, 1.0f);

			InitGeometry();
		}

		void Rectangle::AddTexture(UEGraphics::MATERIAL_TEXTURE type, glm::vec2 position, glm::vec2 size)
		{
			m_Textured = true;
			glm::vec2 positionFloat;
			
			if (type == UEGraphics::MATERIAL_TEXTURE::DIFFUSE)
			{
				positionFloat = glm::vec2(position.x / m_Material->diffuse.GetWidth(), position.y / m_Material->diffuse.GetHeight());
				m_Vertices[0].texCoord = positionFloat;
				m_Vertices[1].texCoord = positionFloat + glm::vec2(size.x / m_Material->diffuse.GetWidth(), 0.0f);
				m_Vertices[2].texCoord = positionFloat + glm::vec2(size.x / m_Material->diffuse.GetWidth(), size.y / m_Material->diffuse.GetHeight());
				m_Vertices[3].texCoord = positionFloat + glm::vec2(0.0f, size.y / m_Material->diffuse.GetHeight());
			}
			else if (type == UEGraphics::MATERIAL_TEXTURE::SPECULAR)
			{
				positionFloat = glm::vec2(position.x / m_Material->specular.GetWidth(), position.y / m_Material->specular.GetHeight());
				m_Vertices[0].texCoord = positionFloat;
				m_Vertices[1].texCoord = positionFloat + glm::vec2(size.x / m_Material->specular.GetWidth(), 0.0f);
				m_Vertices[2].texCoord = positionFloat + glm::vec2(size.x / m_Material->specular.GetWidth(), size.y / m_Material->specular.GetHeight());
				m_Vertices[3].texCoord = positionFloat + glm::vec2(0.0f, size.y / m_Material->specular.GetHeight());
			}
		}

	}
}