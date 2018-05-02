#include "SimpleRenderer3D.h"

namespace VoxEngine
{
	namespace Graphics
	{
		//--------------------------------------------------------------------------------//
		//**************************************Mics**************************************//
		//--------------------------------------------------------------------------------//
		void SimpleRenderer3D::LinkShader(Shader& shader)
		{
			m_Shader = &shader;
		}

		void SimpleRenderer3D::AddToQueue(VEEntity::Entity& entity)
		{
			m_EntityQueue.push_back(&entity);
		}

		void SimpleRenderer3D::Render()
		{
			while (!m_EntityQueue.empty())
			{
				VEEntity::Entity* entity = m_EntityQueue.front();
				std::vector<std::string> listName = entity->GetEntityComponentsList(VEEntity::EntityComponentType::Graphic);

				VEEntity::Model* model;

				for (int i(0); i < listName.size(); i++)
				{
					model = &entity->GetComponent<VEEntity::Model>(listName[i]);

					/*for (int i(0); i < model->GetMeshesNumber(); 0)
					{
						VEEntity::Mesh* mesh = &model->m_Meshes[0];

						m_Shader->SetUniformMat4("model", glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));

						glBindTexture(GL_TEXTURE0, -1);
						glBindTexture(GL_TEXTURE1, -1);

						mesh->GetVAO()->Bind();
						mesh->GetEBO()->Bind();

						glDrawElements(GL_TRIANGLES, mesh->GetEBO()->GetCount(), GL_UNSIGNED_INT, nullptr);

						mesh->GetEBO()->Unbind();
						mesh->GetVAO()->Unbind();

						glBindTexture(GL_TEXTURE0, 0);
						glBindTexture(GL_TEXTURE1, 0);
					}*/
				}

				m_EntityQueue.pop_front();

			}
		}

	}
}