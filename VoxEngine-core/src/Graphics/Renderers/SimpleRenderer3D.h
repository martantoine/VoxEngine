#pragma once

#ifdef UE_EMSCRIPTEN
	#define GLFW_INCLUDE_ES3
	#include <GLFW\glfw3.h>
#else
	#include <GL/glew.h>
	#include <GLFW\glfw3.h>
#endif

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
			//Constructors
			SimpleRenderer3D();
			SimpleRenderer3D(Shader& shader);
			
			//Miscs
			void LinkShader(Shader& shader);
			
			//Rendering stuff
			void AddToQueue(UEntity::Entity& entity);
			void Render(UEntity::Entity& entity);
			void Render();

		private:
			std::deque<UEntity::Entity*> m_EntityQueue;
			Shader* m_Shader;
		};

	}
}