#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <iostream>
#include <string>
#include "Mesh.h"
#include "../../EntityComponent.h"

namespace VoxEngine
{
	namespace VEEntity
	{

		class Model : public EntityComponent
		{
		public:
			//Constructors
			Model();
			Model(const char* path);

			//EntityComponent's functions
			void LoadModel(const char* path);
			void processNode(aiNode *node, const aiScene *scene);
			Mesh processMesh(aiMesh *mesh, const aiScene *scene);
			unsigned int GetMeshesNumber();

			std::vector<Mesh> m_Meshes;
		private:
			std::string m_Path, m_Directory;
			glm::vec3 m_Color;
			glm::mat4 m_lTranslation, m_lRotation, m_lScale;
			bool m_Textured;
			EntityComponentType m_EntityComponentType;
		};

	}
}