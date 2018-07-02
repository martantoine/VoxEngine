#include "Renderable.h"

namespace UE
{
	namespace UEntity
	{

		//-------------------------------------------------------------------------------//
		//***********************************Materials***********************************//
		//-------------------------------------------------------------------------------//
		void Renderable::AddMaterial(UEGraphics::Material& material)
		{
			m_Material = &material;
			SetTextures();
		}

		UEGraphics::Material& Renderable::GetMaterial() const
		{
			return *m_Material;
		}



		//-------------------------------------------------------------------------------//
		//***********************************Buffers***********************************//
		//-------------------------------------------------------------------------------//
		UEGraphics::VAO* Renderable::GetVAO() const
		{
			return m_VAO;
		}

		UEGraphics::EBO* Renderable::GetEBO() const
		{
			return m_EBO;
		}

		bool Renderable::isTextured() const
		{
			return m_Textured;
		}

	}
}