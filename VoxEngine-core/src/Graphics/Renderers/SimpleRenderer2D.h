#pragma once

#include <GL\glew.h>
#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\mat4x4.hpp>
#include <deque>
#include "../../Entities/Components/Renderable/Shapes/Renderable2D.h"
#include "../../Entities/Entity.h"
#include "../Shaders/Shader.h"

namespace UE
{
	namespace UEGraphics 
	{
		
		class SimpleRenderer2D
		{
		public:
			//Miscs
			void LinkShader(Shader& shader);
			void AddToQueue(UEntity::Entity& entity);
			void Render();

		private:
			std::deque<UEntity::Entity*> m_EntityQueue;
			Shader* m_Shader;
		};

	}
}