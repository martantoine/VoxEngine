#pragma once

#include "../EntityComponent.h"

namespace UE
{
	namespace UEntity
	{

		class PointLight : public EntityComponent
		{
		public:
			//Constructors
			PointLight();
			PointLight(glm::vec3 position);
			
			//EntityComponent's functions
			void SetParameters(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
			void SetColor(glm::vec3 color);

			glm::vec3 GetAmbient() const;
			glm::vec3 GetDiffuse() const;
			glm::vec3 GetSpecular() const;

		private:
			glm::vec3 m_Ambient;
			glm::vec3 m_Diffuse;
			glm::vec3 m_Specular;
		};

	}
}