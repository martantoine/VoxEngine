#pragma once

#include <GL/glew.h>
#include <vector>
#include "../../../../Graphics/Buffers/Vertex.h"
#include "../../../../Graphics/Buffers/Texture.h"

namespace VoxEngine
{
	namespace VEEntity
	{

		struct Mesh
		{
			Mesh() {}
			Mesh(std::vector<VertexData> vertices, std::vector<GLuint> indices, std::vector<Graphics::Texture> textures)
			{
				m_Vertices = vertices;
				m_Indices = indices;
				m_Textures = textures;
			}

			std::vector<VertexData> m_Vertices;
			std::vector<GLuint> m_Indices;
			std::vector<Graphics::Texture> m_Textures;
		};

	}
}