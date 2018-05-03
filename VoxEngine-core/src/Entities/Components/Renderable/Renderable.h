#pragma once

#include <GLM\glm.hpp>
#include "../../../Graphics/Buffers/Buffers.h"
#include "../../../Materials/Material.h"
#include "../EntityComponent.h"

namespace VoxEngine
{
	namespace VEEntity
	{

		class Renderable : public EntityComponent
		{
		public:
			//Constructors
			Renderable();
			Renderable(glm::vec3 position);
			Renderable(glm::vec3 position, float angle, glm::vec3 axis);

			//Geometry initialize
			virtual void Init() = 0;

			//Materials
			void AddMaterial(Graphics::Material& material);
			Graphics::Material& GetMaterial() const;

			//Buffers
			Graphics::VAO* GetVAO() const;
			Graphics::EBO* GetEBO() const;

			Graphics::Texture* GetTexture() const {}
			bool isTextured() const;

			//Miscs
			virtual unsigned int GetMeshesNumber() { return 0; }

		protected:
			Graphics::VAO* m_VAO;
			Graphics::EBO* m_EBO;
			VertexData* m_Vertices;

			Graphics::Material* m_Material;
			bool m_Textured;
		};

	}
}