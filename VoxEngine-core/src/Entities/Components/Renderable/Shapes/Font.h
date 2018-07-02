#pragma once

#ifdef UE_EMSCRIPTEN
	#define GLFW_INCLUDE_ES3
	#include <GLFW\glfw3.h>
#else
	#include <GL/glew.h>
	#include <GLFW\glfw3.h>
#endif

#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>
#include <iostream>
#include "Character.h"

namespace UE
{
	namespace UEntity
	{

		class Font
		{
		public:
			//Constructors
			Font();
			Font(const char* path, int pixelSize);
			
			//Initializer
			void Init(const char* path, int pixelSize);
			Character GetChar(GLchar character);

		private:
			std::map<GLchar, Character> m_Characters;
		};

	}
}