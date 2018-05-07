#pragma once

#include <GLM/glm.hpp>
#include <vector>
#include "../../../Graphics/Buffers/Buffers.h"
#include "../../../Materials/Material.h"
#include "../EntityComponent.h"
#include "Models\Mesh.h"

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
			virtual void Init(const char* modelPath) = 0;

			//Materials
			void AddMaterial(Graphics::Material& material);
			Graphics::Material& GetMaterial() const;

			//Buffers
			Graphics::VAO* GetVAO() const;
			Graphics::EBO* GetEBO() const;
			virtual Mesh& GetMesh(int i) = 0;
			virtual int GetMeshesNbr() = 0;
			bool isTextured() const;

		protected:
			Graphics::VAO* m_VAO;
			Graphics::EBO* m_EBO;

			std::vector<Graphics::Texture> textures_loaded;
			Graphics::Material* m_Material;
			bool m_Textured;
		};

	}
}