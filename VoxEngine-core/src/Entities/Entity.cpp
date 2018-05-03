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



		//-------------------------------------------------------------------------------//
		//*************************************Miscs*************************************//
		//-------------------------------------------------------------------------------//
		void Entity::AddComponent(std::string name, EntityComponent& component)
		{
			m_EntityComponents[name] = component;
		}

		void Entity::AddComponent(std::string name, Renderable& component)
		{
			m_RenderableComponents[name] = &component;
		}

		Renderable* Entity::GetComponent(std::string name)
		{
			return m_RenderableComponents[name];
		}

		std::vector<std::string> Entity::GetEntityComponentsList(EntityComponentType type)
		{
			std::vector<std::string> list;

			if(type == EntityComponentType::GRAPHIC)
				for (auto& component : m_RenderableComponents)
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