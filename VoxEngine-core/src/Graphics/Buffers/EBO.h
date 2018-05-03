#pragma once

#include <GL\glew.h>
#include <vector>

namespace VoxEngine {
	namespace Graphics {

		class EBO
		{
		public:
			//Constructors
			EBO();
			EBO(GLuint* data, int count);

			//Ininitalizers
			void CreateEBO(GLuint* data, int count);

			//Miscs
			GLuint GetCount() const;
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