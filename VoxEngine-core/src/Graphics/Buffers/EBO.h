#pragma once

#include <GL\glew.h>
#include <vector>

namespace VoxEngine {
	namespace Graphics {

		class EBO
		{
		public:
			EBO(GLushort* data, int count);
			EBO(std::vector<GLuint> data, int count);

			inline GLuint GetCount() const { return m_Count; }

			void Bind() const;
			void Unbind() const;


			void Destroy();
			~EBO();

		private:
			GLuint m_EBO;
			GLuint m_Count;
		};

	}
}