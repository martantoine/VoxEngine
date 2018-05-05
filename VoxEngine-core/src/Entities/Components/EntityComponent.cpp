#include "EntityComponent.h"

namespace VoxEngine
{
	namespace VEEntity
	{
		//--------------------------------------------------------------------------------//
		//**********************************Constructors**********************************//
		//--------------------------------------------------------------------------------//
		EntityComponent::EntityComponent()
		{
			m_lScale = glm::mat4(1.0f);
			m_lRotation = glm::mat4(1.0f);
			m_lTranslation = glm::mat4(1.0f);
		}

		EntityComponent::EntityComponent(glm::vec3 position)
		{
			m_lScale = glm::mat4(1.0f);
			m_lRotation = glm::mat4(1.0f);
			m_lTranslation = glm::translate(glm::mat4(1.0f), position);
		}

		EntityComponent::EntityComponent(glm::vec3 position, float angle, glm::vec3 axis)
		{
			m_lScale = glm::mat4(1.0f);
			m_lRotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
			m_lTranslation = glm::translate(glm::mat4(1.0f), position);
		}



		//-------------------------------------------------------------------------------//
		//*************************************Miscs*************************************//
		//-------------------------------------------------------------------------------//
		EntityComponentType EntityComponent::GetType() const
		{
			return m_EntityComponentType;
		}



		//-------------------------------------------------------------------------------//
		//********************************Transformations********************************//
		//-------------------------------------------------------------------------------//
		glm::mat4 EntityComponent::GetTransformation() const
		{
			return m_lScale * m_lRotation * m_lTranslation;
		}

		///Translatio
		glm::vec3 EntityComponent::GetPosition()
		{
			return glm::vec3(m_lTranslation[3][0], m_lTranslation[3][1], m_lTranslation[3][1]);
		}

		void EntityComponent::SetPosition(glm::vec3 position)
		{
			m_lTranslation = glm::translate(glm::mat4(1.0f), position);
		}

		void EntityComponent::Move(glm::vec3 offset)
		{
			m_lTranslation = glm::translate(m_lTranslation, offset);
		}

		///Rotation
		glm::mat4 EntityComponent::GetRotation() const
		{
			return m_lRotation;
		}

		void EntityComponent::SetRotation(float angle, glm::vec3 axis)
		{
			m_lRotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
		}

		void EntityComponent::Rotate(float angle, glm::vec3 axis)
		{
			m_lRotation = glm::rotate(m_lRotation, glm::radians(angle), axis);
		}

		///Homothety
		glm::mat4 EntityComponent::GetScale() const
		{
			return m_lScale;
		}

		void EntityComponent::SetScale(glm::vec3 scale)
		{
			m_lScale = glm::scale(glm::mat4(1.0f), scale);
		}

		void EntityComponent::Scale(glm::vec3 scale)
		{
			m_lScale = glm::scale(m_lScale, scale);
		}

	}
}