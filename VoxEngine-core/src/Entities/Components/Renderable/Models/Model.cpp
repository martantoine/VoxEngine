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
			m_EntityComponentType = EntityComponentType::GRAPHIC;
			m_Textured = false;
			m_Path = modelPath;

			m_lScale = glm::mat4(1.0f);
			m_lRotation = glm::mat4(1.0f);
			m_lTranslation = glm::mat4(1.0f);
			
			Init();
		}

		Model::Model(const char* modelPath, glm::vec3 position)
		{
			m_EntityComponentType = EntityComponentType::GRAPHIC;
			m_Textured = false;
			m_Path = modelPath;

			m_lScale = glm::mat4(1.0f);
			m_lRotation = glm::mat4(1.0f);
			m_lTranslation = glm::translate(glm::mat4(1.0f), position);

			Init();
		}

		Model::Model(const char* modelPath, glm::vec3 position, float angle, glm::vec3 axis)
		{
			m_EntityComponentType = EntityComponentType::GRAPHIC;
			m_Textured = false;
			m_Path = modelPath;

			m_lScale = glm::mat4(1.0f);
			m_lRotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
			m_lTranslation = glm::translate(glm::mat4(1.0f), position);

			Init();
		}



		//-------------------------------------------------------------------------------//
		//*****************************Geometry initialize*******************************//
		//-------------------------------------------------------------------------------//
		void Model::Init()
		{
			///Loading scene
			Assimp::Importer import;
			const aiScene *scene = import.ReadFile(m_Path, aiProcess_Triangulate | aiProcess_FlipUVs);

			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
				return;
			}
			m_Directory = m_Path.substr(0, m_Path.find_last_of('/'));

			processNode(scene->mRootNode, scene);


			const unsigned int meshesNbr = m_Meshes.size();
			m_VAO = new Graphics::VAO[meshesNbr];
			m_EBO = new Graphics::EBO[meshesNbr];

			for (unsigned int i(0); i < meshesNbr; i++)
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

			for (unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				VertexData vertex;
				glm::vec3 vector;
				vector.x = mesh->mVertices[i].x;
				vector.y = mesh->mVertices[i].y;
				vector.z = mesh->mVertices[i].z;
				vertex.vertice = vector;
				vector.x = mesh->mNormals[i].x;
				vector.y = mesh->mNormals[i].y;
				vector.z = mesh->mNormals[i].z;
				vertex.color = glm::vec3(1.0f, 1.0f, 1.0f);
				vertex.normal = vector;
				vertex.texCoord = glm::vec2(0.0f, 0.0f);
				vertices.push_back(vertex);
			}
			
			std::vector<GLuint> indices;
			for (unsigned int i = 0; i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];
				for (unsigned int j = 0; j < face.mNumIndices; j++)
					indices.push_back(face.mIndices[j]);
			}

			return Mesh(vertices, indices);
		}

		unsigned int Model::GetMeshesNumber()
		{
			return m_Meshes.size();
		}

	}
}