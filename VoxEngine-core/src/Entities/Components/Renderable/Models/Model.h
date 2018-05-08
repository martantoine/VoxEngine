#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>
#include <iostream>
#include "../Renderable.h"
#include "Mesh.h"
#include "../../../../Graphics/Buffers/Texture.h"
#include "../../../../Graphics/Buffers/Image.h"

namespace UE
{
	namespace UEntity
	{

		class Model : public Renderable
		{
		public:
			//Constructors
			Model();
			Model(const char* modelPath);
			Model(const char* modelPath, glm::vec3 position);
			Model(const char* modelPath, glm::vec3 position, float angle, glm::vec3 axis);

			//Miscs
			Mesh& GetMesh(int i);
			int GetMeshesNbr();

			//Geometry initialize
			void InitGeometry(const char* modelPath = 0);
			
		private:
			//Geometry initialize
			void processNode(aiNode *node, const aiScene *scene);
			Mesh processMesh(aiMesh *mesh, const aiScene *scene);
			std::vector<UEGraphics::Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

		private:
			std::vector<Mesh> m_Meshes;
			std::string m_Directory;
		};

	}
}