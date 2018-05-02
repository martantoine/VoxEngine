#pragma once

#include "../../../Graphics/Buffers/Buffers.h"
#include "../EntityComponent.h"
#include "../../../Materials/Material.h"

namespace VoxEngine
{
	namespace VEEntity
	{

		class Renderable : public EntityComponent
		{
		public:
			//EntityComponent's functions
			///Miscs
			void Init() {}

			///Materials
			void AddMaterial(Graphics::Material* material);
			Graphics::Material GetMaterial();

			///Colors
			void SetColor(glm::vec3 color);
			glm::vec3 GetColor() const;

			///Buffers
			Graphics::VAO* GetVAO() const;
			Graphics::EBO* GetEBO() const;
			Graphics::Texture* GetTexture() const;
			void AddTexture(Graphics::Texture& texture, glm::vec2 position, glm::vec2 size);
			bool isTextured();

		protected:
			Graphics::VAO* m_VAO;
			Graphics::EBO* m_EBO;
			VertexData* m_Vertices;
			glm::vec3* m_Normal;
			GLushort* m_Indices;
			Graphics::Material* m_Material;

			glm::vec3 m_Color;
			bool m_Textured;

		};

	}
}