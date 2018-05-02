#pragma once

#include <GL\glew.h>
#include <GLM\glm.hpp>
#include <vector>
#include "Vertex.h"

namespace VoxEngine {
	namespace Graphics {

		class VBO
		{
		public:
			VBO() {}
			VBO(glm::vec3* data, int count, GLuint componentCount);
			VBO(std::vector<glm::vec3> data, int count, GLuint componentCount);

			inline GLuint GetComponentCount() { return m_ComponentCount; }

			void Bind() const;
			void Unbind() const;

			void Destroy();
			~VBO();

		private:
			GLuint m_VBO;
			GLuint m_ComponentCount;
		};

	}
}