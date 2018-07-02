#pragma once

#ifdef UE_EMSCRIPTEN
	#define GLFW_INCLUDE_ES3
	#include <GLFW\glfw3.h>
#else
	#include <GL/glew.h>
	#include <GLFW\glfw3.h>
#endif

#include <vector>
#include "VBO.h"
#include "Vertex.h"

namespace UE
{
	namespace UEGraphics
	{
		
		class VAO
		{
		public:
			//Constructors
			VAO();

			//Initializer
			void AddVBO(VBO* vbo, GLuint index, vertexDataVar var);
			
			//Miscs
			void Bind() const;
			void Unbind() const;
			void ClearVBO();

			//Destructors
			void Destroy();
			~VAO();

		private:
			GLuint m_VAO;
			std::vector<VBO*> m_VBOs;
		};

	}
}