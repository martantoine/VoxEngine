#pragma once

#include <GL\glew.h>
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