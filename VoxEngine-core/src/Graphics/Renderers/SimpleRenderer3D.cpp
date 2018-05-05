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

					for (int MeshOffset(0); MeshOffset < renderable->GetMeshesNumber(); MeshOffset++)
					{
						int diffuseNbr(1);
						int specularNbr(1);
						for (int TextureOffset(0); TextureOffset < renderable->GetMesh(MeshOffset).m_Textures.size(); TextureOffset++)
						{
							std::string typeStr = renderable->GetMesh(MeshOffset).m_Textures[TextureOffset].GetType().c_str();
							int number(0);
							if (typeStr == "texture_diffuse")
								number = (diffuseNbr++);
							else if (typeStr == "texture_specular")
								number = (specularNbr++);
							typeStr += std::to_string(number);
							const char* typeChar = typeStr.c_str();

							glActiveTexture(GL_TEXTURE0 + TextureOffset);
							//m_Shader->SetUniformTexture(typeChar, TextureOffset); //Uniform
							//renderable->GetMesh(MeshOffset).m_Textures[TextureOffset].Bind(); //Bind

							glUniform1i(glGetUniformLocation(m_Shader->GetShader(), typeChar), TextureOffset);
							// and finally bind the texture
							glBindTexture(GL_TEXTURE_2D, renderable->GetMesh(MeshOffset).m_Textures[TextureOffset].GetTextureID());
						}

						m_Shader->SetUniformMat4("model", entity->GetTransformation() * renderable->GetTransformation());
						VAO* tmpVAO = renderable->GetVAO();
						EBO* tmpEBO = renderable->GetEBO();

						tmpVAO[MeshOffset].Bind();	
						tmpEBO[MeshOffset].Bind();

						glDrawElements(GL_TRIANGLES, tmpEBO[MeshOffset].GetCount(), GL_UNSIGNED_INT, nullptr);

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