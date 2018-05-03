#pragma once

#include "../../../../Graphics/Buffers/Buffers.h"
#include "../../EntityComponent.h"

namespace VoxEngine
{
	namespace VEEntity
	{

		class Shapes : public EntityComponent
		{
		public:
			//EntityComponent's functions
			///Transformations
			void SetPosition(glm::vec3 position);
			void Move(glm::vec3 offset);
			void SetRotation(float angle, glm::vec3 axis);
			void Rotate(float angle, glm::vec3 axis);
			void SetScale(glm::vec3 scale);
			void Scale(glm::vec3 scale);
			glm::mat4 GetTransformation() const;

			///Others
			glm::vec3 GetColor() const;
			void SetColor(glm::vec3 color);
			void virtual UpdateShape() = 0;

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
			Graphics::Texture* m_Texture;

			glm::mat4 m_Transformations;
			glm::vec3 m_Color;

			bool m_Textured;
		};

	}
}