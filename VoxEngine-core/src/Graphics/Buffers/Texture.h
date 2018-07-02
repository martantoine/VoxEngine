#pragma once

#ifdef UE_EMSCRIPTEN
	#define GLFW_INCLUDE_ES3
	#include <GLFW\glfw3.h>
#else
	#include <GL/glew.h>
	#include <GLFW\glfw3.h>
#endif

#include <string>
#include "../Buffers/Image.h"

namespace UE
{
	namespace UEGraphics
	{

		class Texture
		{
		public:
			//Constructors
			Texture();
			Texture(Image* image); //No image saved
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