#pragma once

#include "../Renderable.h"

namespace UE
{
	namespace UEntity
	{

		class Renderable2D : public Renderable
		{
		public:

		protected:
			VertexData* m_Vertices;
			GLushort* m_Indices;
		};

	}
}