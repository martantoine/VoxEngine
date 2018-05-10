#pragma once

#include <string>
#include "../../../../Graphics/Shaders/Shader.h"
#include "../../EntityComponent.h"
#include "Rectangle.h"
#include "Font.h"

namespace UE
{
	namespace UEntity
	{

		class Text : public EntityComponent
		{
		public:
			//Constructors
			Text(Font& font, std::string text, glm::vec2 position, GLfloat scale);
			
			//Initializer
			void Init();
			
			//Draw
			void Draw(UEGraphics::Shader& shader);

		private:
			Font& m_Font;
			std::string m_Text;
			std::vector<Rectangle> m_Rect;
			std::vector<Character> m_Char;
			glm::vec3 Position;
		};

	}
}