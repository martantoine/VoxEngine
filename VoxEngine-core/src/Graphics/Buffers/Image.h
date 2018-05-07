#pragma once


#include <iostream>
#include <GL/glew.h>
#include "../../Utils/ImageLoader.h"

namespace VoxEngine
{
	namespace VEGraphics
	{

		struct Image
		{
			Image(const char* path)
			{
				Load(path);
			}
			
			bool Load(const char* path)
			{
				data = stbi_load(path, &width, &height, &componentsNbr, 0);
				if (!data)
				{
					std::cout << "ERROR::ASSIMP::Failed to load a texture at " << path << " !\n";
					return false;
				}
				return true;
			}
		
			
			GLubyte* data;
			int width, height, componentsNbr;
		};

	}
}