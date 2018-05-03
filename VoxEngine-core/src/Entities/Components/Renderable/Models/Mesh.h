#pragma once

#include <vector>
#include "../../../../Graphics/Buffers/Vertex.h"

namespace VoxEngine
{
	namespace VEEntity
	{

		struct Mesh
		{
			Mesh() {}
			Mesh(std::vector<VertexData> vertices, std::vector<unsigned int> indices)
			{
				m_Vertices = vertices;
				m_Indices = indices;
			}

			std::vector<VertexData> m_Vertices;
			std::vector<unsigned int> m_Indices;
		};

	}
}