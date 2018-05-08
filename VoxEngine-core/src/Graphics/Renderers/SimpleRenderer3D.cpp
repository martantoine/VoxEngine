#include "SimpleRenderer3D.h"

namespace UE
{
	namespace UEGraphics
	{
		//--------------------------------------------------------------------------------//
		//**************************************Mics**************************************//
		//--------------------------------------------------------------------------------//
		void SimpleRenderer3D::LinkShader(Shader& shader)
		{
			m_Shader = &shader;
		}

		void SimpleRenderer3D::AddToQueue(UEntity::Entity& entity)
		{
			m_EntityQueue.push_back(&entity);
		}

		void SimpleRenderer3D::Render()
		{
			while (!m_EntityQueue.empty())
			{
				UEntity::Entity* entity = m_EntityQueue.front();
				std::vector<std::string> listName = entity->GetEntityComponentsList(UEntity::EntityComponentType::GRAPHIC3D);

				for (int ECOffset(0); ECOffset < listName.size(); ECOffset++)
				{
					UEntity::Model* renderable = entity->Get3DComponent(listName[ECOffset]);

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
								m_Shader->SetUniform1i("textured", 1);
							}
						}
						else
							m_Shader->SetUniform1i("textured", 0);

						VAO* tmpVAO = renderable->GetVAO();
						EBO* tmpEBO = renderable->GetEBO();

						tmpVAO[MeshOffset].Bind();	
						tmpEBO[MeshOffset].Bind();

						m_Shader->SetUniformMat4("model", entity->GetTransformation() * renderable->GetTransformation());
						m_Shader->Bind();

						glDrawElements(GL_TRIANGLES, tmpEBO[MeshOffset].GetCount(), GL_UNSIGNED_INT, nullptr);

						tmpEBO[MeshOffset].Unbind();
						tmpVAO[MeshOffset].Unbind();

						for (GLuint TextureOffset(0); TextureOffset < renderable->GetMesh(MeshOffset).m_Textures.size(); TextureOffset++)
							renderable->GetMesh(MeshOffset).m_Textures[TextureOffset].Unbind();

						glActiveTexture(GL_TEXTURE0);
					}
				}

				m_EntityQueue.pop_front();

			}
		}

	}
}