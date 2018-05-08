#pragma once

#include <GL\glew.h>
#include <GLM\glm.hpp>
#include <vector>
#include "Vertex.h"

namespace UE
{
	namespace UEGraphics
	{

		class VBO
		{
		public:
			//Constructors
			VBO() {}
			VBO(glm::vec3* data, int count, GLuint componentCount);
			VBO(std::vector<glm::vec3> data, int count, GLuint componentCount);

			//Miscs
			void Bind() const;
			void Unbind() const;
			GLuint GetComponentCount();

			//Destructors
			void Destroy();
			~VBO();

		private:
			GLuint m_VBO;
			GLuint m_ComponentCount;
		};

	}
}