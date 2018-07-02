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
			SetUniformLocation("textured");
			SetUniformLocation("light.position");
			SetUniformLocation("light.ambient");
			SetUniformLocation("light.diffuse");
			SetUniformLocation("light.specular");
			SetUniformLocation("viewPosition");
			SetUniformLocation("texture_specular1");

			Bind();
			SetUniformTexture("texture_diffuse1", 0);
			SetUniformTexture("texture_specular1", 1);
			Unbind();
		}

		void LightingShader::SetLight(UEntity::PointLight& light)
		{
			SetUniform3("light.position", light.GetPosition());
			SetUniform3("light.ambient", light.GetAmbient());
			SetUniform3("light.diffuse", light.GetDiffuse());
			SetUniform3("light.specular", light.GetSpecular());
		}
	}
}