#pragma once

#include <GLM\vec3.hpp>
#include "../Graphics/Buffers/Texture.h"

namespace VoxEngine
{
	namespace Graphics
	{

		enum MATERIAL_TEXTURE { DIFFUSE, SPECULAR };

		struct Material
		{
			//Functions
			///Constructors
			Material() {}
			Material(Graphics::Texture* diffuse, Graphics::Texture* specular, float shininess)
				: diffuse(diffuse), specular(specular), shininess(shininess) {}

			///Miscs
			void SetParameters(Graphics::Texture* Diffuse, Graphics::Texture* Specular, float Shininess)
			{
				diffuse = Diffuse;
				specular = Specular;
				shininess = Shininess;
			}


			//Variables
			Graphics::Texture* diffuse;
			Graphics::Texture* specular;
			float shininess;
		};

	}
}