#pragma once

#include "../Renderable.h"

namespace VoxEngine
{
	namespace VEEntity
	{

		class Rectangle : public Renderable
		{
		public:
			//Constructors
			Rectangle();
			Rectangle(glm::vec3 position, glm::vec2 size, float angle, glm::vec3 axis, glm::vec3 color);

<<<<<<< HEAD
			//Geometry initialize
			void InitGeometry();

			//Textures
			void AddTexture(VEGraphics::MATERIAL_TEXTURE type);
			void AddTexture(VEGraphics::MATERIAL_TEXTURE type, glm::vec2 position, glm::vec2 size);

=======
			//EntityComponent's functions
			void AddTexture(Graphics::MATERIAL_TEXTURE type);
			void AddTexture(Graphics::MATERIAL_TEXTURE type, glm::vec2 position, glm::vec2 size);
			void InitGeometry();
>>>>>>> parent of aa0b869... Save before renderable update

		private:
			glm::vec2 m_Size;
		};

	}
}