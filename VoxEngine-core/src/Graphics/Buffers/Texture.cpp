#include "Texture.h"

namespace UE
{
	namespace UEGraphics
	{

		//--------------------------------------------------------------------------------//
		//**********************************Constructors**********************************//
		//--------------------------------------------------------------------------------//	
		Texture::Texture()
		{
		}
		
		Texture::Texture(Image& image)
		{
			SetImage(image);
		}



		//--------------------------------------------------------------------------------//
		//***********************************Initializer**********************************//
		//--------------------------------------------------------------------------------//	
		void Texture::SetImage(Image& image)
		{
			m_Width = image.width;
			m_Height = image.height;

			GLenum format;
			if (image.componentsNbr == 1)
				format = GL_RED;
			else if (image.componentsNbr == 2)
				format = GL_RG;
			else if (image.componentsNbr == 3)
				format = GL_RGB;
			else if (image.componentsNbr == 4)
				format = GL_RGBA;

			m_Texture = new GLuint;
			glGenTextures(1, m_Texture);
			Bind();

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexImage2D(GL_TEXTURE_2D, 0, format, image.width, image.height, 0, format, GL_UNSIGNED_BYTE, image.data);
			glGenerateMipmap(GL_TEXTURE_2D);

			Unbind();
			
			stbi_image_free(image.data);
		}



		//--------------------------------------------------------------------------------//
		//*******************************Binding functionns*******************************//
		//--------------------------------------------------------------------------------//
		void Texture::Bind()
		{
			glBindTexture(GL_TEXTURE_2D, *m_Texture);
		}

		void Texture::Unbind()
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}



		//--------------------------------------------------------------------------------//
		//**********************************Set functions*********************************//
		//--------------------------------------------------------------------------------//
		void Texture::SetType(std::string type)
		{ 
			m_Type = type; 
		}

		void Texture::SetPath(std::string path)
		{ 
			m_Path = path; 
		}

		void Texture::SetName(std::string name)
		{
			m_Name = name;
		}



		//--------------------------------------------------------------------------------//
		//**********************************Get functions*********************************//
		//--------------------------------------------------------------------------------//
		GLuint Texture::GetWidth() const
		{
			return m_Width;
		}

		GLuint Texture::GetHeight() const
		{
			return m_Height;
		}

		std::string Texture::GetType() const
		{ 
			return m_Type; 
		}

		std::string Texture::GetPath() const
		{ 
			return m_Path; 
		}

		std::string Texture::GetName() const
		{
			return m_Name;
		}

		GLuint& Texture::GetTextureID() const
		{
			return *m_Texture;
		}

	}
}