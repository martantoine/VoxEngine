#include "Model.h"

namespace VoxEngine
{
	namespace VEEntity
	{

		//--------------------------------------------------------------------------------//
		//**********************************Constructors**********************************//
		//--------------------------------------------------------------------------------//		
		Model::Model(const char* modelPath)
		{
			///Miscs var
			m_EntityComponentType = EntityComponentType::GRAPHIC;
			m_Textured = false;

			///Transformations var
			m_lScale = glm::mat4(1.0f);
			m_lRotation = glm::mat4(1.0f);
			m_lTranslation = glm::mat4(1.0f);
			
			///Load the model
			Init(modelPath);
		}

		Model::Model(const char* modelPath, glm::vec3 position)
		{
			///Miscs var
			m_EntityComponentType = EntityComponentType::GRAPHIC;
			m_Textured = false;

			///Transformations var
			m_lScale = glm::mat4(1.0f);
			m_lRotation = glm::mat4(1.0f);
			m_lTranslation = glm::translate(glm::mat4(1.0f), position);

			///Load the model
			Init(modelPath);
		}

		Model::Model(const char* modelPath, glm::vec3 position, float angle, glm::vec3 axis)
		{
			///Miscs var
			m_EntityComponentType = EntityComponentType::GRAPHIC;
			m_Textured = false;

			///Transformations var
			m_lScale = glm::mat4(1.0f);
			m_lRotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
			m_lTranslation = glm::translate(glm::mat4(1.0f), position);

			///Load the model
			Init(modelPath);
		}



		//-------------------------------------------------------------------------------//
		//************************************Miscs**************************************//
		//-------------------------------------------------------------------------------//
		GLuint Model::GetMeshesNumber()
		{
			return m_Meshes.size();
		}



		//-------------------------------------------------------------------------------//
		//*****************************Geometry initialize*******************************//
		//-------------------------------------------------------------------------------//
		void Model::Init(const char* modelPath)
		{
			///Loading scene
			Assimp::Importer import;
			const aiScene *scene = import.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);

			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
				return;
			}
			
			processNode(scene->mRootNode, scene);


			const GLuint meshesNbr = m_Meshes.size();
			m_VAO = new Graphics::VAO[meshesNbr];
			m_EBO = new Graphics::EBO[meshesNbr];

			for (GLuint i(0); i < meshesNbr; i++)
			{
				Graphics::VBO* vbo = new Graphics::VBO(&m_Meshes[i].m_Vertices[0].vertice, m_Meshes[i].m_Vertices.size(), 4);

				m_VAO[i].ClearVBO();
				m_VAO[i].AddVBO(vbo, 0, VERTEX);
				m_VAO[i].AddVBO(vbo, 1, NORMAL);
				m_VAO[i].AddVBO(vbo, 2, COLOR);
				if (m_Textured)
					m_VAO[i].AddVBO(vbo, 3, TEXTURE);

				m_EBO[i].CreateEBO(m_Meshes[i].m_Indices.data(), m_Meshes[i].m_Indices.size());
			}
		}

		void Model::processNode(aiNode *node, const aiScene *scene)
		{
			///Process all the node's meshes
			for (unsigned int i = 0; i < node->mNumMeshes; i++)
			{
				aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
				m_Meshes.push_back(processMesh(mesh, scene));
			}
			///Do the same for each of its children
			for (unsigned int i = 0; i < node->mNumChildren; i++)
				processNode(node->mChildren[i], scene);
		}

		Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
		{
			std::vector<VertexData> vertices;

			//VertexData processing
			for (unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				VertexData vertex;
				glm::vec3 vector;

				///Position
				vector.x = mesh->mVertices[i].x;
				vector.y = mesh->mVertices[i].y;
				vector.z = mesh->mVertices[i].z;
				vertex.vertice = vector;
				///Normal
				vector.x = mesh->mNormals[i].x;
				vector.y = mesh->mNormals[i].y;
				vector.z = mesh->mNormals[i].z;
				vertex.normal = vector;
				///Color
				vertex.color = glm::vec3(1.0f, 1.0f, 1.0f);
				///Texture coords
				vertex.texCoord = glm::vec2(0.0f, 0.0f);

				vertices.push_back(vertex);
			}
			
			//Indices processing
			std::vector<GLuint> indices;
			for (GLuint i(0); i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];
				for (GLuint j(0); j < face.mNumIndices; j++)
					indices.push_back(face.mIndices[j]);
			}

			return Mesh(vertices, indices);
		}

	}
}