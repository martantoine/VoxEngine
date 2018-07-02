#pragma once

#include <GLM/vec3.hpp>
#include <GLM/mat4x4.hpp>
#include <vector>
#include <string>
#include <map>
#include <GLM/gtc/matrix_transform.hpp>
#include "Components/EntityComponent.h"
#include "Components/Renderable/Shapes/Renderable2D.h"
#include "Components/Renderable/Models/Model.h"
#include <iostream>

namespace UE
{
	namespace UEntity
	{

		class Entity
		{
		public:
			//Constructors
			Entity();
			Entity(std::string name, EntityComponent& component);
			Entity(std::string name, Renderable2D& component);
			Entity(glm::vec3 position);
			Entity(glm::vec3 position, float angle, glm::vec3 axis);

			//Components
			void AddComponent(std::string name, EntityComponent& component);
			void AddComponent(std::string name, Renderable2D& component);
			void AddComponent(std::string name, Model& component);
			Renderable2D* Get2DComponents(std::string name);
			Model* Get3DComponent(std::string name);

			std::vector<std::string> GetEntityComponentsList(EntityComponentType type);

			//Tranformations
			void SetPosition(glm::vec3 position);
			void Move(glm::vec3 offset);
			glm::mat4 GetTransformation();

		private:
			int count;
			glm::mat4 m_gScale, m_gRotation, m_gTranslation;
			std::map<std::string, EntityComponent> m_EntityComponents;
			std::map<std::string, Renderable2D*> m_Renderable2DComponents;
			std::map<std::string, Model*> m_Renderable3DComponents;
		};

	}
}