#pragma once

#include <GL\glew.h>
#include <vector>
#include "../../../../Graphics/Buffers/Buffers.h"
#include "../../../../Materials/Material.h"
#include "../Renderable.h"

namespace VoxEngine
{
	namespace VEEntity
	{

		class Mesh : public Renderable
		{
		public:
			//Constructors
			Mesh() {}
			Mesh(std::vector<VertexData> vertices, std::vector<GLuint> indices);
			
			//Mesh's functions
			void SetupMesh();

			//Variables
			std::vector<VertexData> m_Vertices;
			std::vector<GLuint> m_Indices;

		private:
			Graphics::VAO* m_VAO;
			Graphics::EBO* m_EBO;
			Graphics::Material* m_Material;

			bool m_Textured;
		};

	}
}