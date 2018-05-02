#include "Texture.h"

namespace VoxEngine {
	namespace Graphics {

		Texture::Texture(Image& image)
			: m_Image(&image)
		{
			m_Texture = new GLuint;
			glGenTextures(1, m_Texture);
			glBindTexture(GL_TEXTURE_2D, *m_Texture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image.data);
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(image.data);
		}

		void Texture::Bind()
		{
			glBindTexture(GL_TEXTURE_2D, *m_Texture);
		}

		void Texture::Unbind()
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

	}
}