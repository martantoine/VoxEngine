#pragma once


#include <iostream>
#include <GL\glew.h>

#include "../../Utils/ImageLoader.h"

namespace VoxEngine {
	namespace Graphics {

		struct Image
		{
			Image(const char* path)
			{
				data = stbi_load(path, &width, &height, nullptr, 0);
				if (!data)
					std::cout << "Failed to load a texture at " << path << " !\n";
			}

			GLubyte* data;
			int width, height;
		};

	}
}