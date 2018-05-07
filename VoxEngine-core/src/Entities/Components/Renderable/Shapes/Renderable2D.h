#pragma once

#include "../../../../Graphics/Buffers/Buffers.h"
#include "../Renderable.h"

namespace VoxEngine
{
	namespace VEEntity
	{

		class Renderable2D : public Renderable
		{
		public:
			//Textures
			virtual void AddTexture(VEGraphics::MATERIAL_TEXTURE type) = 0;
			virtual void AddTexture(VEGraphics::MATERIAL_TEXTURE type, glm::vec2 position, glm::vec2 size) = 0;

		protected:
			VertexData * m_Vertices;
			GLushort* m_Indices;
		};

	}
}