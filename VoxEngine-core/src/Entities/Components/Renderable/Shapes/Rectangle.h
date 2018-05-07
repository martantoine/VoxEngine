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
<<<<<<< HEAD
			//Geometry initialize
			void InitGeometry();

=======
>>>>>>> parent of cb7fd7a... Test
			//Textures
			void AddTexture(Graphics::MATERIAL_TEXTURE type);
			void AddTexture(Graphics::MATERIAL_TEXTURE type, glm::vec2 position, glm::vec2 size);

<<<<<<< HEAD
=======
			//EntityComponent's functions
			void AddTexture(Graphics::MATERIAL_TEXTURE type);
			void AddTexture(Graphics::MATERIAL_TEXTURE type, glm::vec2 position, glm::vec2 size);
			void InitGeometry();
>>>>>>> parent of aa0b869... Save before renderable update
=======
			//Geometry initialize
			void Init();
>>>>>>> parent of cb7fd7a... Test

		private:
			glm::vec2 m_Size;
		};

	}
}