#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <iostream>
#include "../Renderable.h"
#include "Mesh.h"

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

			//Geometry initialize
			void Init(const char* modelPath);
			
		private:
			//Geometry initialize
			void processNode(aiNode *node, const aiScene *scene);
			Mesh processMesh(aiMesh *mesh, const aiScene *scene);


		private:
			std::vector<Mesh> m_Meshes;
		};

	}
}