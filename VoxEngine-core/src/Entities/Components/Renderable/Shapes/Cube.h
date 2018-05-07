#pragma once

#include "../Renderable.h"

namespace VoxEngine
{
	namespace VEEntity
	{

		class Cube : public Renderable
		{
		public:
			//Constructors
			Cube();
			Cube(glm::vec3 position, glm::vec3 size, float angle, glm::vec3 axis, glm::vec3 colors);

			//EntityComponent's functions
			void AddTexture(Graphics::MATERIAL_TEXTURE type);
			void InitGeometry();

		private:
			glm::vec3 m_Size;
		};

	}
}