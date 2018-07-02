#include "SimpleRenderer2D.h"

namespace UE
{
	namespace UEGraphics
	{

		//--------------------------------------------------------------------------------//
		//**********************************Constructors**********************************//
		//--------------------------------------------------------------------------------//
		SimpleRenderer2D::SimpleRenderer2D()
			: m_Shader(nullptr)
		{
		}

		SimpleRenderer2D::SimpleRenderer2D(Shader& shader)
		{
			LinkShader(shader);
		}



		//--------------------------------------------------------------------------------//
		//**************************************Mics**************************************//
		//--------------------------------------------------------------------------------//
		void SimpleRenderer2D::LinkShader(Shader& shader)
		{
			m_Shader = &shader;
		}



		//--------------------------------------------------------------------------------//
		//********************************Rendering stuff*********************************//
		//--------------------------------------------------------------------------------//
		void SimpleRenderer2D::AddToQueue(UEntity::Entity& entity)
		{
			m_EntityQueue.push_back(&entity);
		}

		void SimpleRenderer2D::Render(UEntity::Entity& entity)
		{
			m_EntityQueue.push_back(&entity);
			Render();
		}

		void SimpleRenderer2D::Render()
		{
			m_Shader->Bind();
			m_Shader->SetUniform1i("UI", 1);

			while (!m_EntityQueue.empty())
			{
				UEntity::Entity* entity = m_EntityQueue.front();
				std::vector<std::string> listName = entity->GetEntityComponentsList(UEntity::EntityComponentType::GRAPHIC2D);

				UEntity::Renderable2D* renderable;

				for (int i(0); i < listName.size(); i++)
				{
					renderable = entity->Get2DComponents(listName[i]);
										
					glActiveTexture(GL_TEXTURE0);
					renderable->GetMaterial().diffuse.Bind();
					glActiveTexture(GL_TEXTURE1);
					renderable->GetMaterial().specular.Bind();


					renderable->GetVAO()->Bind();
					renderable->GetEBO()->Bind();

					m_Shader->SetUniform1i("textured", 1);
					m_Shader->SetUniformMat4("model", entity->GetTransformation() * renderable->GetTransformation());
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