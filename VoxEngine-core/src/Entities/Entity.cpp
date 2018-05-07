#include "Entity.h"

namespace VoxEngine
{
	namespace VEEntity
	{
		//--------------------------------------------------------------------------------//
		//**********************************Constructors**********************************//
		//--------------------------------------------------------------------------------//
		Entity::Entity()
		{
			m_gScale = glm::mat4(1.0f);
			m_gRotation = glm::mat4(1.0f);
			m_gTranslation = glm::mat4(1.0f);
		}

		Entity::Entity(glm::vec3 position)
		{
			m_gScale = glm::mat4(1.0f);
			m_gRotation = glm::mat4(1.0f);
			m_gTranslation = glm::translate(glm::mat4(1.0f), position);
		}

		Entity::Entity(glm::vec3 position, float angle, glm::vec3 axis)
		{
			m_gScale = glm::mat4(1.0f);
			m_gRotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
			m_gTranslation = glm::translate(glm::mat4(1.0f), position);
		}



		//-------------------------------------------------------------------------------//
		//*************************************Miscs*************************************//
		//-------------------------------------------------------------------------------//
		void Entity::AddComponent(std::string name, EntityComponent& component)
		{
			m_EntityComponents[name] = component;
		}

		void Entity::AddComponent(std::string name, Renderable2D& component)
		{
			m_Renderable2DComponents[name] = &component;
		}

		void Entity::AddComponent(std::string name, Model& component)
		{
			m_Renderable3DComponents[name] = &component;
		}

		Model* Entity::GetComponent(std::string name)
		{
			return m_Renderable3DComponents[name];
		}

		std::vector<std::string> Entity::GetEntityComponentsList(EntityComponentType type)
		{
			std::vector<std::string> list;

			if(type == EntityComponentType::GRAPHIC)
				for (auto& component : m_Renderable3DComponents)
					list.push_back(component.first);

			return list;
		}



		//-------------------------------------------------------------------------------//
		//********************************Transformations********************************//
		//-------------------------------------------------------------------------------//
		void Entity::SetPosition(glm::vec3 position)
		{
			m_gTranslation = glm::translate(glm::mat4(1.0f), position);
		}

		void Entity::Move(glm::vec3 offset)
		{
			m_gTranslation = glm::translate(m_gTranslation, offset);
		}

		glm::mat4 Entity::GetTransformation()
		{
			return m_gScale * m_gRotation * m_gTranslation;
		}
	}
}