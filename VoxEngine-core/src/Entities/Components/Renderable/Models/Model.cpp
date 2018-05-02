#include "Model.h"

namespace VoxEngine
{
	namespace VEEntity
	{
		//--------------------------------------------------------------------------------//
		//**********************************Constructors**********************************//
		//--------------------------------------------------------------------------------//
		Model::Model()
		{
			m_EntityComponentType = EntityComponentType::Graphic;

			m_Color = glm::vec3(0.4f, 0.4f, 0.4f);
			m_Textured = false;

			m_lScale = glm::mat4(1.0f);
			m_lRotation = glm::mat4(1.0f);
			m_lTranslation = glm::mat4(1.0f);
		}
		
		Model::Model(const char* path)
		{
			m_Path = path;
			m_EntityComponentType = EntityComponentType::Graphic;

			m_Color = glm::vec3(0.9f, 0.4f, 0.4f);
			m_Textured = false;

			m_lScale = glm::mat4(1.0f);
			m_lRotation = glm::mat4(1.0f);
			m_lTranslation = glm::mat4(1.0f);
			
			LoadModel(path);
		}



		//-------------------------------------------------------------------------------//
		//**************************EntityComponent's function***************************//
		//-------------------------------------------------------------------------------//
		void Model::LoadModel(const char* path)
		{
			m_Path = path;
			Assimp::Importer import;
			const aiScene *scene = import.ReadFile(m_Path, aiProcess_Triangulate | aiProcess_FlipUVs);

			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
				return;
			}
			m_Directory = m_Path.substr(0, m_Path.find_last_of('/'));

			processNode(scene->mRootNode, scene);
		}

		void Model::processNode(aiNode *node, const aiScene *scene)
		{
			// process all the node's meshes (if any)
			for (unsigned int i = 0; i < node->mNumMeshes; i++)
			{
				aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
				m_Meshes.push_back(processMesh(mesh, scene));
			}
			// then do the same for each of its children
			for (unsigned int i = 0; i < node->mNumChildren; i++)
			{
				processNode(node->mChildren[i], scene);
			}
		}

		Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
		{
			std::vector<VertexData> vertices;
			std::vector<GLuint> indices;

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