#pragma once

#include <GLM\vec2.hpp>
#include <GLM\vec3.hpp>

namespace UE
{

	enum vertexDataVar {VERTEX, COLOR, TEXTURE, NORMAL};

	struct VertexData
	{
		glm::vec3 vertice;
		glm::vec3 normal;
		glm::vec3 color;
		glm::vec2 texCoord;
	};

}