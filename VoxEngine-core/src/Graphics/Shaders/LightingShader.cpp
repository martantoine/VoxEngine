#include "LightingShader.h"

namespace UE
{
	namespace UEGraphics
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
			SetUniformLocation("UI");

			///Fragment shader uniforms
			SetUniformLocation("texture_diffuse1");
			SetUniformLocation("texture_specular1");
			SetUniformTexture("texture_diffuse1", 0);
			SetUniformTexture("texture_specular1", 1);
			SetUniformLocation("textured");
			SetUniformLocation("light.position");
			SetUniformLocation("light.ambient");
			SetUniformLocation("light.diffuse");
			SetUniformLocation("light.specular");
			SetUniformLocation("viewPosition");
		}

	}
}