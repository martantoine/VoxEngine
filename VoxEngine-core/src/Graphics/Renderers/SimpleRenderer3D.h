#pragma once

#include <GL/glew.h>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/mat4x4.hpp>
#include <deque>
#include <vector>
#include "../Shaders/Shader.h"
#include "../../Entities/Entity.h"
#include "../../Entities/Components/Renderable/Models/Model.h"

namespace VoxEngine
{
	namespace VEGraphics
	{

		class SimpleRenderer3D
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