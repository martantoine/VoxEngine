#pragma once

#include "Components\EntityComponent.h"
#include "Components\Renderable\Renderable.h"
#include "Components\Lights\PointLight.h"

#include <GLM\vec3.hpp>
#include <GLM\mat4x4.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <vector>
#include <string>
#include <map>

namespace VoxEngine
{
	namespace VEEntity
	{

		class Entity
		{
		public:
			//Constructors
			Entity();

			//Miscs
			void AddComponent(std::string name, EntityComponent& component);
			void AddComponent(std::string name, Renderable& component);
			Renderable* GetComponent(std::string name);

			std::vector<std::string> GetEntityComponentsList(EntityComponentType type);

			//Tranformations
			void SetPosition(glm::vec3 position);
			void Move(glm::vec3 offset);
			glm::mat4 GetTransformation();

		private:
			int count;
			glm::mat4 m_gScale, m_gRotation, m_gTranslation;
			std::map<std::string, EntityComponent> m_EntityComponents;
			std::map<std::string, Renderable*> m_RenderableComponents;
		};

	}
}