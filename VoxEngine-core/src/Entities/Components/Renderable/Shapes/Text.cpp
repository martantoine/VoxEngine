#pragma once

#include "Text.h"

namespace UE
{
	namespace UEntity
	{

		//--------------------------------------------------------------------------------//
		//**********************************Constructors**********************************//
		//--------------------------------------------------------------------------------//
		Text::Text(Font& font, std::string text, glm::vec2 position, GLfloat scale)
			: m_Font(font), m_Text(text), Position(glm::vec3(position, 0.0f))
		{
			//Create rectangles
			for (int i(0); i < text.size(); i++)
				m_Rect.push_back(Rectangle());

			m_lTranslation = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
			m_lRotation = glm::mat4(1.0f);
			m_lScale= glm::scale(glm::mat4(1.0f), glm::vec3(scale));

			Init();
		}



		//--------------------------------------------------------------------------------//
		//**********************************Initializer***********************************//
		//--------------------------------------------------------------------------------//
		void Text::Init()
		{
			std::string::const_iterator c;
			int i(0), x(0);
			for (c = m_Text.begin(); c != m_Text.end(); c++)
			{
				Character ch = m_Font.GetChar(*c);

				GLfloat xpos = Position.x + ch.Bearing.x * m_lScale[0][0];
				GLfloat ypos = Position.y - (ch.Size.y - ch.Bearing.y) * m_lScale[1][1];

				GLfloat w = ch.Size.x * m_lScale[0][0];
				GLfloat h = ch.Size.y * m_lScale[1][1];

				m_Rect[i].SetParameters(glm::vec3(xpos, ypos, 0.0f), glm::vec2(w, h), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
				m_Rect[i].AddTexture(UEGraphics::DIFFUSE);
				i++;
				Position.x += (ch.Advance >> 6) * m_lScale[0][0];
				m_Char.push_back(ch);
			}
		}



		//--------------------------------------------------------------------------------//
		//*************************************Draw***************************************//
		//--------------------------------------------------------------------------------//
		void Text::Draw(UEGraphics::Shader &shader)
		{
			for (int i(0); i < m_Text.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, m_Char[i].TextureID);

				m_Rect[i].GetVAO()->Bind();;
				m_Rect[i].GetEBO()->Bind();

				shader.Bind();
				shader.SetUniform1i("UI", 1);
				shader.SetUniform1i("textured", 1);
				shader.SetUniformMat4("model", m_Rect[i].GetTransformation());
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);

				m_Rect[i].GetEBO()->Unbind();
				m_Rect[i].GetVAO()->Unbind();
			}
		}
	}
}