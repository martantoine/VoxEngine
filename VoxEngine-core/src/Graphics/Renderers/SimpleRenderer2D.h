#pragma once

#include <GL\glew.h>
#include <deque>
#include "../../Entities/Components/Renderable/Renderable.h"
#include "../../Entities/Entity.h"
#include "../Shaders/Shader.h"
#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\mat4x4.hpp>
#include "../../Entities/Components/Renderable/Models/Mesh.h"

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