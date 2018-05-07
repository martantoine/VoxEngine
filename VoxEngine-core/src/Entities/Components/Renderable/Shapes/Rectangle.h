#pragma once

#include "Renderable2D.h"

namespace VoxEngine
{
	namespace VEEntity
	{

		class Rectangle : public Renderable2D
		{
		public:
			//Constructors
			Rectangle();
			Rectangle(glm::vec3 position) {}
			Rectangle(glm::vec3 position, float angle, glm::vec3 axis, glm::vec3 color) {}
			Rectangle(glm::vec3 position, glm::vec2 size, float angle, glm::vec3 axis, glm::vec3 color);

			//Geometry initialize
			void InitGeometry();

			//Textures
			void AddTexture(VEGraphics::MATERIAL_TEXTURE type);
			void AddTexture(VEGraphics::MATERIAL_TEXTURE type, glm::vec2 position, glm::vec2 size);


		private:
			glm::vec2 m_Size;
		};

	}
}