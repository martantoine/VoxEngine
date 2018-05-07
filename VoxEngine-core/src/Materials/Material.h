#pragma once

#include <GLM\vec3.hpp>
#include "../Graphics/Buffers/Texture.h"

namespace VoxEngine
{
	namespace VEGraphics
	{

		enum MATERIAL_TEXTURE { DIFFUSE, SPECULAR };

		struct Material
		{
			//Functions
			///Constructors
			Material() {}
			Material(VEGraphics::Texture* diffuse, VEGraphics::Texture* specular, float shininess)
				: diffuse(diffuse), specular(specular), shininess(shininess) {}

			///Miscs
			void SetParameters(VEGraphics::Texture* Diffuse, VEGraphics::Texture* Specular, float Shininess)
			{
				diffuse = Diffuse;
				specular = Specular;
				shininess = Shininess;
			}


			//Variables
			VEGraphics::Texture* diffuse;
			VEGraphics::Texture* specular;
			float shininess;
		};

	}
}