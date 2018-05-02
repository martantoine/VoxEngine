#pragma once

#include <GL\glew.h>
#include "../Buffers/Image.h"

namespace VoxEngine {
	namespace Graphics {

		class Texture
		{
		public:
			Texture() {}
			Texture(Image& image);

			void Bind();
			void Unbind();
			
			int GetWidth() { return m_Image->width; }
			int GetHeight() { return m_Image->height; }

		private:
			GLuint* m_Texture;
			Image* m_Image;
		};

	}
}