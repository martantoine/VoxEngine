#pragma once

#include <GLM\glm.hpp>
#include "../../../Graphics/Buffers/Buffers.h"
#include "../../../Materials/Material.h"
#include "../EntityComponent.h"
#include "Models\Mesh.h"

namespace UE
{
	namespace UEntity
	{

		class Renderable : public EntityComponent
		{
		public:
			//Constructors
			Renderable() {}
			Renderable(glm::vec3 position) {}
			Renderable(glm::vec3 position, float angle, glm::vec3 axis) {}

			//Geometry initialize
			virtual void InitGeometry(const char* modelPath = 0) = 0;

			//Materials
			void AddMaterial(UEGraphics::Material& material);
			UEGraphics::Material& GetMaterial() const;
			virtual void SetTextures() {}

			//Buffers
			UEGraphics::VAO* GetVAO() const;
			UEGraphics::EBO* GetEBO() const;
			bool isTextured() const;

		protected:
			UEGraphics::VAO* m_VAO;
			UEGraphics::EBO* m_EBO;

			std::vector<UEGraphics::Texture> textures_loaded;
			UEGraphics::Material* m_Material;
			bool m_Textured;
		};

	}
}