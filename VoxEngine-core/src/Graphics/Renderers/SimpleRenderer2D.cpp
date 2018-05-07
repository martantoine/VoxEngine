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
				VEEntity::Entity* entity = m_EntityQueue.front();
				std::vector<std::string> listName = entity->GetEntityComponentsList(VEEntity::EntityComponentType::Graphic);

				VEEntity::Renderable renderableEntity;
				VEEntity::Model modelEntity;

				for (int i(0); i < listName.size(); i++)
				{
					//Regular
					/*renderableEntity = entity->GetGraphicComponent(listName[i]);

					glm::mat4 m = renderableEntity.GetTransformation() * entity->GetTransformation();
					m_Shader->SetUniformMat4("model", m);

					if (renderableEntity.isTextured())
					{
						glActiveTexture(GL_TEXTURE0);
						renderableEntity.GetMaterial().diffuse->Bind();
						glActiveTexture(GL_TEXTURE1);
						renderableEntity.GetMaterial().specular->Bind();
					}
					else
					{
						glBindTexture(GL_TEXTURE0, -1);
						glBindTexture(GL_TEXTURE1, -1);
					}
					renderableEntity.GetVAO()->Bind();
					renderableEntity.GetEBO()->Bind();

					glDrawElements(GL_TRIANGLES, renderableEntity.GetEBO()->GetCount(), GL_UNSIGNED_SHORT, nullptr);

					renderableEntity.GetEBO()->Unbind();
					renderableEntity.GetVAO()->Unbind();

					glBindTexture(GL_TEXTURE0, 0);
					glBindTexture(GL_TEXTURE1, 0);*/


					//Model
					/*modelEntity = entity->GetModelComponent(listName[i]);

						VEEntity::Mesh* mesh = &modelEntity.m_Meshes[0];

						m_Shader->SetUniformMat4("model", glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));

					//	glBindTexture(GL_TEXTURE0, -1);
					//	glBindTexture(GL_TEXTURE1, -1);

						mesh->GetVAO()->Bind();
						mesh->GetEBO()->Bind();

						glDrawElements(GL_TRIANGLES, mesh->m_Indices.size(), GL_UNSIGNED_INT, nullptr);

						mesh->GetEBO()->Unbind();
						mesh->GetVAO()->Unbind();

					//	glBindTexture(GL_TEXTURE0, 0);
					//	glBindTexture(GL_TEXTURE1, 0);*/
				}

				m_EntityQueue.pop_front();
				
			}
		}

	}
}