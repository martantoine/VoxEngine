#pragma once

#include <GL\glew.h>
#include <vector>
#include "VBO.h"
#include "Vertex.h"

namespace VoxEngine {
	namespace Graphics {
		
		class VAO
		{
		public:
			VAO();
			void AddVBO(VBO* vbo, GLuint index, vertexDataVar var);
			void ClearVBO() { m_VBOs.clear(); }
			void Bind() const;
			void Unbind() const;

			void Destroy();
			~VAO();

		private:
			GLuint m_VAO;
			std::vector<VBO*> m_VBOs;
		};

	}
}