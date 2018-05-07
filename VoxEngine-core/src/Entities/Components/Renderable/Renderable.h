#pragma once

#include <GLM\glm.hpp>
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
<<<<<<< HEAD
			VEGraphics::VAO* GetVAO() const;
			VEGraphics::EBO* GetEBO() const;
=======
			Graphics::VAO* GetVAO() const;
			Graphics::EBO* GetEBO() const;
			virtual Graphics::Texture GetTexture(int mesh, int texture)
			{ return Graphics::Texture(); }
			virtual Mesh GetMesh(int i) 
			{
				return Mesh();
			}
>>>>>>> parent of aa0b869... Save before renderable update
			bool isTextured() const;

			//Miscs
			virtual unsigned int GetMeshesNumber() { return 0; }

		protected:
<<<<<<< HEAD
			VEGraphics::VAO* m_VAO;
			VEGraphics::EBO* m_EBO;
=======
			Graphics::VAO* m_VAO;
			Graphics::EBO* m_EBO;
			VertexData* m_Vertices;
>>>>>>> parent of aa0b869... Save before renderable update

			std::vector<VEGraphics::Texture> textures_loaded;
			VEGraphics::Material* m_Material;
			bool m_Textured;
		};

	}
}