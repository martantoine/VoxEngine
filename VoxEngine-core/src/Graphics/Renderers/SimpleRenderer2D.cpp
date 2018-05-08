#include "SimpleRenderer2D.h"

namespace UE
{
	namespace UEGraphics
	{

		//--------------------------------------------------------------------------------//
		//**************************************Mics**************************************//
		//--------------------------------------------------------------------------------//
		void SimpleRenderer2D::LinkShader(Shader& shader)
		{
			m_Shader = &shader;
		}

		void SimpleRenderer2D::AddToQueue(UEntity::Entity& entity)
		{
			m_EntityQueue.push_back(&entity);
		}

		void SimpleRenderer2D::Render()
		{
			while (!m_EntityQueue.empty())
			{
				UEntity::Entity* entity = m_EntityQueue.front();
				std::vector<std::string> listName = entity->GetEntityComponentsList(UEntity::EntityComponentType::GRAPHIC2D);

				UEntity::Renderable2D* renderable;

				for (int i(0); i < listName.size(); i++)
				{
					renderable = entity->Get2DComponents(listName[i]);

					m_Shader->Bind();
					
					glActiveTexture(GL_TEXTURE0);
					renderable->GetMaterial().diffuse.Bind();
					glActiveTexture(GL_TEXTURE1);
					renderable->GetMaterial().specular.Bind();

					m_Shader->SetUniform1i("textured", 1);

					renderable->GetVAO()->Bind();
					renderable->GetEBO()->Bind();

					m_Shader->SetUniformMat4("model", entity->GetTransformation() * renderable->GetTransformation());
					m_Shader->Bind();
					glDrawElements(GL_TRIANGLES, renderable->GetEBO()->GetCount(), GL_UNSIGNED_SHORT, nullptr);

					renderable->GetEBO()->Unbind();
					renderable->GetVAO()->Unbind();

					renderable->GetMaterial().diffuse.Unbind();
					
				}

				m_EntityQueue.pop_front();
			}
		}

	}
}