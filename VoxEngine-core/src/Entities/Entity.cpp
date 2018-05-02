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
		void Entity::AddComponent(std::string name, EntityComponent component)
		{
			m_EntityComponents[name] = &component;
		}

		void Entity::AddComponent(std::string name, Renderable component)
		{
			m_GraphicComponents[name] = component;
		}
		
		void Entity::AddComponent(std::string name, Model component)
		{
			m_ModelComponents[name] = component;
		}

		std::vector<std::string> Entity::GetEntityComponentsList(EntityComponentType type)
		{
			std::vector<std::string> list;

			for (auto& component : m_ModelComponents)
				//if (component.second.GetType() == EntityComponentType::Graphic)
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