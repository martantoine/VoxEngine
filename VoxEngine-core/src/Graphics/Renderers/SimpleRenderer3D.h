#pragma once

#include <GL/glew.h>
#include <deque>
#include "../../Entities/Components/Renderable/Models/Model.h"
#include "../../Entities/Entities.h"
#include "../Shaders/Shader.h"

namespace UE
{
	namespace UEGraphics
	{

		class SimpleRenderer3D
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