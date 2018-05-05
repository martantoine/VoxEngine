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

namespace VoxEngine
{
	namespace VEEntity
	{

		class Model : public Renderable
		{
		public:
			//Constructors
			Model(const char* modelPath);
			Model(const char* modelPath, glm::vec3 position);
			Model(const char* modelPath, glm::vec3 position, float angle, glm::vec3 axis);

			//Miscs
			GLuint GetMeshesNumber();
			Graphics::Texture GetTexture(int mesh, int texture);
			Mesh GetMesh(int i)
			{
				return m_Meshes[i];
			}

			//Geometry initialize
			void Init(const char* modelPath);
			
		private:
			//Geometry initialize
			void processNode(aiNode *node, const aiScene *scene);
			Mesh processMesh(aiMesh *mesh, const aiScene *scene);
			std::vector<Graphics::Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

		private:
			std::vector<Mesh> m_Meshes;
			std::vector<Graphics::Texture> m_Textures;
			std::string m_Directory;
		};

	}
}