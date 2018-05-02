#include "EntityComponent.h"

namespace VoxEngine
{
	namespace VEEntity
	{
		//--------------------------------------------------------------------------------//
		//**********************************Constructors**********************************//
		//--------------------------------------------------------------------------------//
		EntityComponent::EntityComponent()
			: m_lTranslation(glm::mat4(1.0f)), m_lRotation(glm::mat4(1.0f))
		{
		}

		EntityComponent::EntityComponent(glm::vec3 position)
		{
			m_lTranslation = glm::translate(glm::mat4(1.0f), position);
			m_lRotation = glm::mat4(1.0f);
		}

		EntityComponent::EntityComponent(glm::vec3 position, float angle, glm::vec3 axis)
		{
			m_lTranslation = glm::translate(glm::mat4(1.0f), position);
			m_lRotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
		}



		//-------------------------------------------------------------------------------//
		//*************************************Miscs*************************************//
		//-------------------------------------------------------------------------------//
		EntityComponentType EntityComponent::GetType()
		{
			return m_EntityComponentType;
		}



		//-------------------------------------------------------------------------------//
		//********************************Transformations********************************//
		//-------------------------------------------------------------------------------//
		glm::vec3 EntityComponent::GetPosition() const
		{
			return glm::vec3(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) * m_lTranslation);
			//return glm::vec3(m_lTranslation[0][3], m_lTranslation[1][3], m_lTranslation[2][3]);
		}

		void EntityComponent::SetPosition(glm::vec3 position)
		{
			m_lTranslation = glm::translate(glm::mat4(1.0f), position);
		}

		void EntityComponent::Move(glm::vec3 offset)
		{
			m_lTranslation = glm::translate(m_lTranslation, offset);
		}

		glm::vec3 EntityComponent::GetRotation() const
		{
			std::cout << "WARNING: EntityComponent::GetRotation() is not defined !" << std::endl;
			return glm::vec3(0.0f, 0.0f, 0.0f);
		}

		void EntityComponent::SetRotation(float angle, glm::vec3 axis)
		{
			m_lRotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
		}

		void EntityComponent::Rotate(float angle, glm::vec3 axis)
		{
			m_lRotation = glm::rotate(m_lRotation, glm::radians(angle), axis);
		}

		glm::vec3 EntityComponent::GetScale() const
		{
			return glm::vec3(m_lScale[0][0] * m_lScale[1][0] * m_lScale[2][0], m_lScale[0][1] * m_lScale[1][1] * m_lScale[2][1], m_lScale[0][2] * m_lScale[1][2] * m_lScale[2][2]);
		}

		void EntityComponent::SetScale(glm::vec3 scale)
		{
			m_lScale = glm::scale(glm::mat4(1.0f), scale);
		}

		void EntityComponent::Scale(glm::vec3 scale)
		{
			m_lScale = glm::scale(m_lScale, scale);
		}

		glm::mat4 EntityComponent::GetTransformation() const
		{
			return m_lScale * m_lRotation * m_lTranslation;
		}

	}
}