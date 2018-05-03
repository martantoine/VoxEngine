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
				std::vector<std::string> listName = entity->GetEntityComponentsList(VEEntity::EntityComponentType::GRAPHIC);

				for (int i(0); i < listName.size(); i++)
				{
					VEEntity::Renderable* renderable = entity->GetComponent(listName[i]);

					for (int i(0); i < renderable->GetMeshesNumber(); i++)
					{
						m_Shader->SetUniformMat4("model", glm::mat4(1.0f));

						glBindTexture(GL_TEXTURE0, -1);
						glBindTexture(GL_TEXTURE1, -1);

						VAO* tmpVAO = renderable->GetVAO();
						EBO* tmpEBO = renderable->GetEBO();

						tmpVAO[i].Bind();
						tmpEBO[i].Bind();

						glDrawElements(GL_TRIANGLES, tmpEBO[i].GetCount(), GL_UNSIGNED_INT, nullptr);

						tmpEBO[i].Unbind();
						tmpVAO[i].Unbind();

						glBindTexture(GL_TEXTURE0, 0);
						glBindTexture(GL_TEXTURE1, 0);
					}
				}

				m_EntityQueue.pop_front();

			}
		}

	}
}