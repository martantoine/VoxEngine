#pragma once

#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\mat4x4.hpp>
#include <GLM\vec3.hpp>
#include <GLM\glm.hpp>
#include <iostream>

namespace VoxEngine
{
	namespace VEEntity
	{

		enum EntityComponentType { Graphic, Lighting, Misc };

		class EntityComponent
		{
		public:
			//Constructor
			///EntityComponent constructors only set the transformations
			EntityComponent();
			EntityComponent(glm::vec3 position);
			EntityComponent(glm::vec3 position, float angle, glm::vec3 axis);
			
			//Miscs
			EntityComponentType GetType();

			//Transformations
			glm::vec3 GetPosition() const;
			void SetPosition(glm::vec3 position);
			void Move(glm::vec3 offset);
			glm::vec3 GetRotation() const;
			void SetRotation(float angle, glm::vec3 axis);
			void Rotate(float angle, glm::vec3 axis);
			glm::vec3 GetScale() const;
			void SetScale(glm::vec3 scale);
			void Scale(glm::vec3 scale);
			glm::mat4 GetTransformation() const;

		protected:
			glm::mat4 m_lTranslation, m_lRotation, m_lScale;
			EntityComponentType m_EntityComponentType;
		};

	}
}