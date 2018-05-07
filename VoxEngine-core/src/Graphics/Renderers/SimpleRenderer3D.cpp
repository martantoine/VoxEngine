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

				for (int ECOffset(0); ECOffset < listName.size(); ECOffset++)
				{
					VEEntity::Renderable* renderable = entity->GetComponent(listName[ECOffset]);

					for (int MeshOffset(0); MeshOffset < renderable->GetMeshesNbr(); MeshOffset++)
					{
						///Bind Textures
						GLuint diffuseNbr(1);
						GLuint specularNbr(1);
						if (renderable->GetMesh(MeshOffset).m_Textures.size() > 0)
						{
							for (GLuint TextureOffset(0); TextureOffset < renderable->GetMesh(MeshOffset).m_Textures.size(); TextureOffset++)
							{
								GLuint number(0);
								std::string typeStr = renderable->GetMesh(MeshOffset).m_Textures[TextureOffset].GetType().c_str();
								if (typeStr == "texture_diffuse")
									number = (diffuseNbr++);
								else if (typeStr == "texture_specular")
									number = (specularNbr++);
								typeStr += std::to_string(number);

								glActiveTexture(GL_TEXTURE0 + TextureOffset);
								glUniform1i(glGetUniformLocation(m_Shader->GetShader(), typeStr.c_str()), TextureOffset);
								renderable->GetMesh(MeshOffset).m_Textures[TextureOffset].Bind();
								m_Shader->SetUniform1("textured", true);
							}
						}
						else
							m_Shader->SetUniform1("textured", false);

						VAO* tmpVAO = renderable->GetVAO();
						EBO* tmpEBO = renderable->GetEBO();

						///Bind Buffers
						tmpVAO[MeshOffset].Bind();	
						tmpEBO[MeshOffset].Bind();

						m_Shader->SetUniformMat4("model", entity->GetTransformation() * renderable->GetTransformation());
						m_Shader->Bind();
						glDrawElements(GL_TRIANGLES, tmpEBO[MeshOffset].GetCount(), GL_UNSIGNED_INT, nullptr);

						///Unbind Buffers
						tmpEBO[MeshOffset].Unbind();
						tmpVAO[MeshOffset].Unbind();


						glActiveTexture(GL_TEXTURE0);
					}
				}

				m_EntityQueue.pop_front();
			}
		}

	}
}