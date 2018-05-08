#include "Shader.h"

namespace UE
{
	namespace UEGraphics
	{

		//--------------------------------------------------------------------------------//
		//**********************************Constructors**********************************//
		//--------------------------------------------------------------------------------//
		Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
			: vertexPath(vertexShaderPath), fragmentPath(fragmentShaderPath)
		{
			m_Shader = CreateShader(vertexPath, fragmentPath);
		}

		Shader::Shader()
		{

		}



		//--------------------------------------------------------------------------------//
		//*************************************Miscs**************************************//
		//--------------------------------------------------------------------------------//
		GLuint Shader::CreateShader(const char* vertexShaderPath, const char* FragmentShaderPath)
		{
			vertexPath = vertexShaderPath;
			fragmentPath = FragmentShaderPath;
			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
			GLuint program = glCreateProgram();

			std::string vertexStr = readTextFile(vertexShaderPath);
			std::string fragmentStr = readTextFile(FragmentShaderPath);
			
			const char* vertexSrc = vertexStr.c_str();
			const char* fragmentSrc = fragmentStr.c_str();

			glShaderSource(vertex, 1, &vertexSrc, NULL);
			glCompileShader(vertex);
				
			glShaderSource(fragment, 1, &fragmentSrc, NULL);
			glCompileShader(fragment);

			glAttachShader(program, vertex);
			glAttachShader(program, fragment);
			
			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return program;
		}

		void Shader::Reload()
		{
			std::map<const char*, GLuint> tmp_Locations;
			tmp_Locations = m_Locations;
			Unbind();
			Destroy();
			m_Shader = CreateShader(vertexPath, fragmentPath);
			Bind();
			m_Locations = tmp_Locations;
		}

		void Shader::Bind()
		{
			glUseProgram(m_Shader);
		}

		void Shader::Unbind()
		{
			glUseProgram(0);
		}

		void Shader::Destroy()
		{
			glDeleteProgram(m_Shader);
		}

		Shader::~Shader()
		{
			Destroy();
		}


		//--------------------------------------------------------------------------------//
		//************************************Uniforms************************************//
		//--------------------------------------------------------------------------------//
		void Shader::SetUniformLocation(const char* name)
		{
			m_Locations[name] = glGetUniformLocation(m_Shader, name); 
		}

		void Shader::SetUniformTexture(const char* name, int id)
		{
			Bind();
			glUniform1i(m_Locations[name], id);
			Unbind();
		}

		void Shader::SetUniform1i(const char* name, const int& value)
		{
			Bind();
			glUniform1i(m_Locations[name], value);
			Unbind();
		}

		void Shader::SetUniform1f(const char* name, const float& value)
		{
			Bind();
			glUniform1f(m_Locations[name], value);
			Unbind();
		}

		void Shader::SetUniform2(const char* name, const glm::vec2& vec)
		{
			Bind();
			glUniform2f(m_Locations[name], vec.x, vec.y);
			Unbind();
		}

		void Shader::SetUniform3(const char* name, const glm::vec3& vec)
		{
			Bind();
			glUniform3f(m_Locations[name], vec.x, vec.y, vec.z);
			Unbind();
		}

		void Shader::SetUniform4(const char* name, const glm::vec4& vec)
		{
			Bind();
			glUniform4f(m_Locations[name], vec.x, vec.y, vec.z, vec.w);
			Unbind();
		}

		void Shader::SetUniformMat4(const char* name, const glm::mat4& mat4)
		{
			Bind();
			glUniformMatrix4fv(m_Locations[name], 1, GL_FALSE, glm::value_ptr(mat4));
			Unbind();
		}
		
	}
}