#pragma once

#ifdef UE_EMSCRIPTEN
	#define GLFW_INCLUDE_ES3
	#include <GLFW\glfw3.h>
#else
	#include <GL/glew.h>
	#include <GLFW\glfw3.h>
#endif

#include <string>
#include <vector>
#include <map>
#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include "../../Utils/FileReader.h"

namespace UE
{
	namespace UEGraphics
	{
		
		class Shader
		{
		public:
			//Constructors
			Shader();
			Shader(const char* vertexShaderPath, const char* FragmentShaderPath);

			//Miscs
			GLuint CreateShader(const char* vertexShaderPath, const char* FragmentShaderPath);
			GLuint GetShader() { return m_Shader; }
			void Destroy();
			~Shader();

			//Binding stuff
			void Bind();
			void Unbind();
			void CheckBinding();

			//Uniforms
			void SetUniformLocation(const char* name);
			void SetUniformTexture(const char* name, int id);
			void SetUniform1i(const char* name, const int &value);
			void SetUniform1f(const char* name, const float &value);
			void SetUniform2(const char* name, const glm::vec2 &vec);
			void SetUniform3(const char* name, const glm::vec3 &vec);
			void SetUniform4(const char* name, const glm::vec4 &vec);
			void SetUniformMat4(const char* name, const glm::mat4& mat4);

		protected:
			GLuint m_Shader;
			const char *vertexPath, *fragmentPath;
			std::map<const char*, GLuint> m_Locations;
			bool isBind;
		};

	}
}