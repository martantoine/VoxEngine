#include "LightingShader.h"

namespace VoxEngine
{
	namespace Graphics
	{

		//--------------------------------------------------------------------------------//
		//**********************************Constructors**********************************//
		//--------------------------------------------------------------------------------//
		LightingShader::LightingShader(const char* vertexShaderPath, const char* fragmentShaderPath)
		{
			vertexPath = vertexShaderPath;
			fragmentPath = fragmentShaderPath;
			m_Shader = CreateShader(vertexPath, fragmentPath);
			Init();
		}



		//--------------------------------------------------------------------------------//
		//*************************************Miscs**************************************//
		//--------------------------------------------------------------------------------//
		void LightingShader::Init()
		{
			///Vertex shader uniforms
			SetUniformLocation("projection");
			SetUniformLocation("model");
			SetUniformLocation("view");
			SetUniformLocation("explosion");

			///Fragment shader uniforms
			SetUniformLocation("texture_diffuse1");
			SetUniformLocation("texture_specular1");
			SetUniformLocation("textured");
			SetUniformLocation("light.position");
			SetUniformLocation("light.ambient");
			SetUniformLocation("light.diffuse");
			SetUniformLocation("light.specular");
			SetUniformLocation("viewPosition");
		}

	}
}