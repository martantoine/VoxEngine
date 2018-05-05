#pragma once

#include <GLM\glm.hpp>
#include <GLM\vec3.hpp>
#include <GLM\mat4x4.hpp>
#include <GLM\gtc\matrix_transform.hpp>

namespace VoxEngine
{
	namespace VEEntity
	{

		enum EntityComponentType { GRAPHIC, LIGHT, MISC };

		class EntityComponent
		{
		public:
			//Constructors
			EntityComponent();
			EntityComponent(glm::vec3 position);
			EntityComponent(glm::vec3 position, float angle, glm::vec3 axis);

			//Miscs
			EntityComponentType GetType() const;

			//Transformations
			glm::mat4 GetTransformation() const;
			///Translation
			glm::vec3 GetPosition();
			void SetPosition(glm::vec3 position);
			void Move(glm::vec3 offset);
			///Rotation
			glm::mat4 GetRotation() const;
			void SetRotation(float angle, glm::vec3 axis);
			void Rotate(float angle, glm::vec3 axis);
			///Homothety
			glm::mat4 GetScale() const;
			void SetScale(glm::vec3 scale);
			void Scale(glm::vec3 scale);

		protected:
			glm::mat4 m_lTranslation, m_lRotation, m_lScale;
			EntityComponentType m_EntityComponentType;
		};

	}
}