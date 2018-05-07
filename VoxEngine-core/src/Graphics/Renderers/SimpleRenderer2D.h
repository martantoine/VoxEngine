#pragma once

#include <GL/glew.h>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/mat4x4.hpp>
#include <deque>
#include <vector>
#include "../../Entities/Components/Renderable/Renderable.h"
#include "../../Entities/Entity.h"
#include "../Shaders/Shader.h"

namespace VoxEngine
{
	namespace VEGraphics 
	{
		
		class SimpleRenderer2D
		{
		public:
			//Miscs
			void LinkShader(Shader& shader);
			void AddToQueue(VEEntity::Entity& entity);
			void Render();

		private:
			std::deque<VEEntity::Entity*> m_EntityQueue;
			Shader* m_Shader;
		};

	}
}