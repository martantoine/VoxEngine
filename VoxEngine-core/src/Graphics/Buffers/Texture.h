#pragma once

#include <GL/glew.h>
#include <string>
#include "../Buffers/Image.h"

namespace VoxEngine
{
	namespace VEGraphics
	{

		class Texture
		{
		public:
			//Constructors
			Texture();
			Texture(Image& image);
			
			//Initializer
			void SetImage(Image& image);

			//Binding functions
			void Bind();
			void Unbind();

			//Set functions
			void SetType(std::string type);
			void SetPath(std::string path);
			void SetName(std::string name);

			//Get functions
			GLuint GetWidth() const;
			GLuint GetHeight() const;
			std::string GetType() const;
			std::string GetPath() const;
			std::string GetName() const;
			GLuint& GetTextureID() const;

		private:
			GLuint* m_Texture;
			GLuint m_Width, m_Height;
			std::string m_Type, m_Path, m_Name;
		};

	}
}