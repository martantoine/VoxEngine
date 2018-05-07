#include "SimpleRenderer2D.h"

namespace VoxEngine
{
	namespace VEGraphics
	{

		//--------------------------------------------------------------------------------//
		//**************************************Mics**************************************//
		//--------------------------------------------------------------------------------//
		void SimpleRenderer2D::LinkShader(Shader& shader)
		{
			m_Shader = &shader;
		}

		void SimpleRenderer2D::AddToQueue(VEEntity::Entity& entity)
		{
			m_EntityQueue.push_back(&entity);
		}

		void SimpleRenderer2D::Render()
		{
			while (!m_EntityQueue.empty())
			{
				/*VEEntity::Entity* entity = m_EntityQueue.front();
				std::vector<std::string> listName = entity->GetEntityComponentsList(VEEntity::EntityComponentType::GRAPHIC);

				VEEntity::Renderable* renderable;

				for (int ECOffset(0); ECOffset < listName.size(); ECOffset++)
				{
					VEEntity::Entity* entity = m_EntityQueue.front();
					std::vector<std::string> listName = entity->GetEntityComponentsList(VEEntity::EntityComponentType::GRAPHIC);

					if (renderable->isTextured())
					{
						glActiveTexture(GL_TEXTURE0);
						glUniform1i(glGetUniformLocation(m_Shader->GetShader(), "texture_diffuse1"), 0);
						renderable->GetMaterial().diffuse->Bind();
						glActiveTexture(GL_TEXTURE1);
						glUniform1i(glGetUniformLocation(m_Shader->GetShader(), "texture_specular1"), 1);
						renderable->GetMaterial().specular->Bind();
					}

					renderable->GetVAO()->Bind();
					renderable->GetEBO()->Bind();

					m_Shader->SetUniformMat4("model", entity->GetTransformation() * renderable->GetTransformation());
					m_Shader->Bind();
					glDrawElements(GL_TRIANGLES, renderable->GetEBO()->GetCount(), GL_UNSIGNED_SHORT, nullptr);

					renderable->GetEBO()->Unbind();
					renderable->GetVAO()->Unbind();

					glActiveTexture(GL_TEXTURE0);

				}*/

				m_EntityQueue.pop_front();
				
			}
		}

	}
}