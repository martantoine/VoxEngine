#include "Renderable.h"

namespace VoxEngine
{
	namespace VEEntity
	{
		//--------------------------------------------------------------------------------//
		//**********************************Constructors**********************************//
		//--------------------------------------------------------------------------------//
		Renderable::Renderable()
		{
			m_EntityComponentType = EntityComponentType::GRAPHIC;
			m_lScale = glm::mat4(1.0f);
			m_lRotation = glm::mat4(1.0f);
			m_lTranslation = glm::mat4(1.0f);
			m_Textured = false;
		}

		Renderable::Renderable(glm::vec3 position)
		{
			m_EntityComponentType = EntityComponentType::GRAPHIC;
			m_lScale = glm::mat4(1.0f);
			m_lRotation = glm::mat4(1.0f);
			m_lTranslation = glm::translate(glm::mat4(1.0f), position);
			m_Textured = false;
		}

		Renderable::Renderable(glm::vec3 position, float angle, glm::vec3 axis)
		{
			m_EntityComponentType = EntityComponentType::GRAPHIC;
			m_lScale = glm::mat4(1.0f);
			m_lRotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
			m_lTranslation = glm::translate(glm::mat4(1.0f), position);
			m_Textured = false;
		}



		//-------------------------------------------------------------------------------//
		//***********************************Materials***********************************//
		//-------------------------------------------------------------------------------//
		void Renderable::AddMaterial(VEGraphics::Material& material)
		{
			m_Material = &material;
		}

		VEGraphics::Material& Renderable::GetMaterial() const
		{
			return *m_Material;
		}



		//-------------------------------------------------------------------------------//
		//***********************************Buffers***********************************//
		//-------------------------------------------------------------------------------//
		VEGraphics::VAO* Renderable::GetVAO() const
		{
			return m_VAO;
		}

		VEGraphics::EBO* Renderable::GetEBO() const
		{
			return m_EBO;
		}

		bool Renderable::isTextured() const
		{
			return m_Textured;
		}

	}
}