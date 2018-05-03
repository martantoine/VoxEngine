#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <iostream>
#include <string>
#include "../Renderable.h"

namespace VoxEngine
{
	namespace VEEntity
	{

		struct Mesh
		{
			Mesh() {}
			Mesh(std::vector<VertexData> vertices, std::vector<GLuint> indices)
			{
				m_Vertices = vertices;
				m_Indices = indices;
			}

			std::vector<VertexData> m_Vertices;
			std::vector<GLuint> m_Indices;
		};

		class Model : public Renderable
		{
		public:
			//Constructors
			Model(const char* modelPath);
			Model(const char* modelPath, glm::vec3 position);
			Model(const char* modelPath, glm::vec3 position, float angle, glm::vec3 axis);

			//Geometry initialize
			void Init();
			
		private:
			//Geometry initialize
			void processNode(aiNode *node, const aiScene *scene);
			Mesh processMesh(aiMesh *mesh, const aiScene *scene);

			unsigned int GetMeshesNumber();

		private:
			std::string m_Path, m_Directory;
			std::vector<Mesh> m_Meshes;
		};

	}
}