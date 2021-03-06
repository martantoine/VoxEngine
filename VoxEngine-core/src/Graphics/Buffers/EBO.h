#pragma once

#ifdef UE_EMSCRIPTEN
	#define GLFW_INCLUDE_ES3
	#include <GLFW\glfw3.h>
#else
	#include <GL/glew.h>
	#include <GLFW\glfw3.h>
#endif

#include <vector>

namespace UE
{
	namespace UEGraphics
	{

		class EBO
		{
		public:
			//Constructors
			EBO();
			EBO(GLushort* data, int count);
			EBO(GLuint* data, int count);

			//Initializer
			void CreateEBO(GLushort* data, int count);
			void CreateEBO(GLuint* data, int count);

			//Miscs
			void Bind() const;
			void Unbind() const;
			GLuint GetCount() const;

			//Destructors
			void Destroy();
			~EBO();

		private:
			GLuint m_EBO;
			GLuint m_Count;
		};

	}
}