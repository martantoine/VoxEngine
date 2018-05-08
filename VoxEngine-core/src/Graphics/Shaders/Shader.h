#pragma once

#include <GL/glew.h>
#include <string>
#include <vector>
#include <map>
#include <GLM\glm.hpp>
#include <GLM\gtc\type_ptr.hpp>
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
			void Reload();
			void Bind();
			void Unbind();
			GLuint GetShader() { return m_Shader; }

			//Uniforms
			void SetUniformLocation(const char* name);
			void SetUniformTexture(const char* name, int id);
			void SetUniform1i(const char* name, const int &value);
			void SetUniform1f(const char* name, const float &value);
			void SetUniform2(const char* name, const glm::vec2 &vec);
			void SetUniform3(const char* name, const glm::vec3 &vec);
			void SetUniform4(const char* name, const glm::vec4 &vec);
			void SetUniformMat4(const char* name, const glm::mat4& mat4);

			void Destroy();
			~Shader();

		protected:
			GLuint m_Shader;
			std::map<const char*, GLuint> m_Locations;
			const char *vertexPath, *fragmentPath;
		};

	}
}