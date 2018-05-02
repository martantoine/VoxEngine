#include "Shapes.h"

namespace VoxEngine
{
	namespace VEEntity
	{
		//-------------------------------------------------------------------------------//
		//**************************EntityComponent's functions**************************//
		//-------------------------------------------------------------------------------//
		///Tranformations
		void Shapes::SetPosition(glm::vec3 position)
		{
			m_lTranslation = glm::translate(glm::mat4(1.0f), position);
			UpdateShape();
		}

		void Shapes::Move(glm::vec3 offset)
		{
			m_lTranslation = glm::translate(m_lTranslation, offset);
			//UpdateShape();
		}

		void Shapes::SetRotation(float angle, glm::vec3 axis)
		{
			m_lRotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
			UpdateShape();
		}

		void Shapes::Rotate(float angle, glm::vec3 axis)
		{
			m_lRotation = glm::rotate(m_lRotation, glm::radians(angle), axis);
			UpdateShape();
		}

		void Shapes::SetScale(glm::vec3 scale)
		{
			m_lScale = glm::scale(glm::mat4(1.0f), scale);
			UpdateShape();
		}

		void Shapes::Scale(glm::vec3 scale)
		{
			m_lScale = glm::scale(m_lScale, scale);
			UpdateShape();
		}

		glm::mat4 Shapes::GetTransformation() const
		{
			return m_lScale * m_lRotation * m_lTranslation;
		}

		///Other
		glm::vec3 Shapes::GetColor() const
		{
			return m_Color;
		}

		void Shapes::SetColor(glm::vec3 color)
		{
			m_Color = color;
			UpdateShape();
		}


		///Buffers
		Graphics::VAO* Shapes::GetVAO() const
		{ 
			return m_VAO;
		}

		Graphics::EBO* Shapes::GetEBO() const
		{ 
			return m_EBO;
		}

		Graphics::Texture* Shapes::GetTexture() const
		{ 
			return m_Texture;
		}

		bool Shapes::isTextured()
		{ 
			return m_Textured;
		}

	}
}