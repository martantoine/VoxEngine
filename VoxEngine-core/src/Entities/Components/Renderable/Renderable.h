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
			virtual void InitGeometry(const char* modelPath) = 0;

			//Materials 2D
			void AddMaterial(VEGraphics::Material& material);
			VEGraphics::Material& GetMaterial() const;

			//Buffers
			VEGraphics::VAO* GetVAO() const;
			VEGraphics::EBO* GetEBO() const;
			bool isTextured() const;

		protected:
			VEGraphics::VAO* m_VAO;
			VEGraphics::EBO* m_EBO;

			std::vector<VEGraphics::Texture> textures_loaded;
			VEGraphics::Material* m_Material;
			bool m_Textured;
		};

	}
}