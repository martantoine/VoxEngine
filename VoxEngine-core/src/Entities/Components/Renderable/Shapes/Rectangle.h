#pragma once

#include "Renderable2D.h"

namespace UE
{
	namespace UEntity
	{

		class Rectangle : public Renderable2D
		{
		public:
			//Constructors
			Rectangle();
			Rectangle(glm::vec3 position, glm::vec2 size, float angle, glm::vec3 axis, glm::vec3 color);

			//Geometry initialize
			void InitGeometry(const char* modelPath = 0);

			//Textures
			void AddTexture(UEGraphics::MATERIAL_TEXTURE type);
			void AddTexture(UEGraphics::MATERIAL_TEXTURE type, glm::vec2 position, glm::vec2 size);

		private:
			glm::vec2 m_Size;
		};

	}
}