#pragma once

#include <GL\glew.h>
#include <vector>

namespace VoxEngine {
	namespace VEGraphics {

		class EBO
		{
		public:
			//Constructors
			EBO();
			EBO(GLuint* data, int count);

			//Initializer
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