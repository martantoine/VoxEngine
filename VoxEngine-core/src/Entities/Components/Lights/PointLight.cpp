#pragma once

#include "PointLight.h"

namespace VoxEngine
{
	namespace VEEntity
	{
		//--------------------------------------------------------------------------------//
		//**********************************Constructors**********************************//
		//--------------------------------------------------------------------------------//
		PointLight::PointLight()
		{
			m_EntityComponentType = EntityComponentType::Lighting;

			m_lTranslation = glm::mat4(1.0f);
			m_lRotation = glm::mat4(1.0f);
			m_lScale = glm::mat4(1.0f);
		}

		PointLight::PointLight(glm::vec3 position)
		{
			m_EntityComponentType = EntityComponentType::Lighting;

			m_lTranslation = glm::translate(glm::mat4(1.0f), position);
			m_lRotation = glm::mat4(1.0f);
			m_lScale = glm::mat4(1.0f);
		}

		//-------------------------------------------------------------------------------//
		//**************************EntityComponent's functions**************************//
		//-------------------------------------------------------------------------------//
		void PointLight::SetParameters(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
		{
			m_Ambient = ambient;
			m_Diffuse = diffuse;
			m_Specular = specular;
		}

		void PointLight::SetColor(glm::vec3 color)
		{
			m_Diffuse = color;
		}

		glm::vec3 PointLight::GetAmbient() const
		{
			return m_Ambient;
		}

		glm::vec3 PointLight::GetDiffuse() const
		{
			return m_Diffuse;
		}

		glm::vec3 PointLight::GetSpecular() const
		{
			return m_Specular;
		}

	}
}