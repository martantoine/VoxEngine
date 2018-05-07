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
			InitGeometry(modelPath);
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
			InitGeometry(modelPath);
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
			InitGeometry(modelPath);
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
		void Model::InitGeometry(const char* modelPath)
		{
			///Loading scene
			Assimp::Importer import;
			const aiScene *scene = import.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);

			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
				return;
			}

			std::string path(modelPath);
			m_Directory = path.substr(0, path.find_last_of('/'));
			processNode(scene->mRootNode, scene);


			const GLuint meshesNbr = m_Meshes.size();
			m_VAO = new VEGraphics::VAO[meshesNbr];
			m_EBO = new VEGraphics::EBO[meshesNbr];

			///Creating VAO and VBOs for each meshes
			for (GLuint i(0); i < meshesNbr; i++)
			{
				VEGraphics::VBO* vbo = new VEGraphics::VBO(&m_Meshes[i].m_Vertices.data()->vertice, m_Meshes[i].m_Vertices.size(), 4);

				m_VAO[i].ClearVBO();
				m_VAO[i].AddVBO(vbo, 0, VERTEX);
				m_VAO[i].AddVBO(vbo, 1, NORMAL);
				m_VAO[i].AddVBO(vbo, 2, COLOR);
				m_VAO[i].AddVBO(vbo, 3, TEXTURE);

				m_EBO[i].CreateEBO(m_Meshes[i].m_Indices.data(), m_Meshes[i].m_Indices.size());
			}
		}


		void Model::processNode(aiNode *node, const aiScene *scene)
		{
			///Process all the node's meshes
			for (unsigned int i(0); i < node->mNumMeshes; i++)
			{
				aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
				m_Meshes.push_back(processMesh(mesh, scene));
			}
			///Do the same for each of its children
			for (unsigned int i(0); i < node->mNumChildren; i++)
				processNode(node->mChildren[i], scene);
		}

		Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
		{
			//Variables
			std::vector<VertexData> vertices;
			std::vector<GLuint> indices;
			std::vector<VEGraphics::Texture> textures;

			//VertexData processing
			for (unsigned int i(0); i < mesh->mNumVertices; i++)
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
				if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
				{
					vertex.texCoord.x = mesh->mTextureCoords[0][i].x;
					vertex.texCoord.y = mesh->mTextureCoords[0][i].y;
				}
				else
					vertex.texCoord = glm::vec2(0.0f, 0.0f);

				vertices.push_back(vertex);
			}
			
			//Indices processing
			for (GLuint i(0); i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];
				for (GLuint j(0); j < face.mNumIndices; j++)
					indices.push_back(face.mIndices[j]);
			}

			//Materials processing
			if (mesh->mMaterialIndex >= 0) //Check if the mesh has material(s)
			{
				aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
				std::vector<VEGraphics::Texture> diffuseMaps = loadMaterialTextures(material,	aiTextureType_DIFFUSE, "texture_diffuse");
				textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

				std::vector<VEGraphics::Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
				textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
			}

			return Mesh(vertices, indices, textures);
		}

		std::vector<VEGraphics::Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
		{
			std::vector<VEGraphics::Texture> textures;

			for (unsigned int i(0); i < mat->GetTextureCount(type); i++)
			{
				aiString pathAi;
				mat->GetTexture(type, i, &pathAi);
				std::string path = pathAi.C_Str();
				bool skip(false);

				for (int TLOffset(0); TLOffset < textures_loaded.size(); TLOffset++)
				{
					if (std::strcmp(textures_loaded[TLOffset].GetPath().data(), pathAi.C_Str()) == 0)
					{
						textures.push_back(textures_loaded[TLOffset]);
						skip = true;
						break;
					}
				}
				if (!skip)
				{
					VEGraphics::Image image(path.c_str());
					VEGraphics::Texture texture(image);
					texture.SetType(typeName);
					texture.SetPath(path);

					textures_loaded.push_back(texture);
					textures.push_back(texture);
				}
			}
			return textures;
		}

		Graphics::Texture Model::GetTexture(int mesh, int texture)
		{
			return m_Meshes[mesh].m_Textures[texture];
		}
	}
}