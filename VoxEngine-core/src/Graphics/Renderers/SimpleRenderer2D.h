#pragma once

#ifdef UE_EMSCRIPTEN
	#define GLFW_INCLUDE_ES3
	#include <GLES3/gl3.h>
	#include <GLFW/glfw3.h>
#else
	#include <GL/glew.h>
	#include <GLFW/glfw3.h>
#endif

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
			//Constructors
			SimpleRenderer2D();
			SimpleRenderer2D(Shader& shader);

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