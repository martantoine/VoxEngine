#include "Renderable.h"

namespace VoxEngine
{
	namespace VEEntity
	{
		//-------------------------------------------------------------------------------//
		//**************************EntityComponent's functions**************************//
		//-------------------------------------------------------------------------------//
		///Colors
		void Renderable::SetColor(glm::vec3 color)
		{
			m_Color = color;
		}

		glm::vec3 Renderable::GetColor() const
		{
			return m_Color;
		}


		///Materials
		void Renderable::AddMaterial(Graphics::Material* material)
		{
			m_Material = material;
		}

		Graphics::Material Renderable::GetMaterial()
		{
			return *m_Material;
		}


		///Buffers
		Graphics::VAO* Renderable::GetVAO() const
		{
			return m_VAO;
		}

		Graphics::EBO* Renderable::GetEBO() const
		{
			return m_EBO;
		}

		bool Renderable::isTextured()
		{
			return m_Textured;
		}

	}
}