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

					for (int j(0); j < renderable->GetMeshesNumber(); j++)
					{
						m_Shader->SetUniformMat4("model", entity->GetTransformation() * renderable->GetTransformation());

						for (int x(0); x < renderable->GetMesh(j).m_Textures.size(); x++)
						{
							glActiveTexture(GL_TEXTURE0 + x);
							std::string a = renderable->GetMesh(j).m_Textures[x].GetType().c_str();
							a += '1';
							const char* b = a.c_str();
							renderable->GetTexture(j, x).Bind();
							m_Shader->SetUniformTexture(b, renderable->GetMesh(j).m_Textures[x].GetID());
						}

						VAO* tmpVAO = renderable->GetVAO();
						EBO* tmpEBO = renderable->GetEBO();

						tmpVAO[j].Bind();	
						tmpEBO[j].Bind();

						glDrawElements(GL_TRIANGLES, tmpEBO[j].GetCount(), GL_UNSIGNED_INT, nullptr);

						tmpEBO[j].Unbind();
						tmpVAO[j].Unbind();
						glActiveTexture(GL_TEXTURE0);
					}
				}

				m_EntityQueue.pop_front();

			}
		}

	}
}