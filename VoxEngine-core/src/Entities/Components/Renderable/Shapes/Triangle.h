#pragma once

#include "Shapes.h"

namespace VoxEngine {
	namespace Graphics {

		class Triangle : public Shapes
		{
		public:
			Triangle() {}
			Triangle(glm::vec3 position, glm::vec3 side1, glm::vec3 side2);
			void UpdateShape();

		private:
			VertexData* m_Vertices;
			GLushort* m_Indices;
		};

	}
}