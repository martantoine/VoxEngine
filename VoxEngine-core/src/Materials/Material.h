#pragma once

#include <GLM\vec3.hpp>
#include "../Graphics/Buffers/Texture.h"

namespace UE
{
	namespace UEGraphics
	{

		enum MATERIAL_TEXTURE { DIFFUSE, SPECULAR };

		struct Material
		{
			//Functions
			///Constructors
			Material(UEGraphics::Texture& diffuse, UEGraphics::Texture& specular, float shininess)
				: diffuse(diffuse), specular(specular), shininess(shininess) {}

			///Miscs
			void SetParameters(UEGraphics::Texture& Diffuse, UEGraphics::Texture& Specular, float Shininess)
			{
				diffuse = Diffuse;
				specular = Specular;
				shininess = Shininess;
			}


			//Variables
			UEGraphics::Texture& diffuse;
			UEGraphics::Texture& specular;
			float shininess;
		};

	}
}