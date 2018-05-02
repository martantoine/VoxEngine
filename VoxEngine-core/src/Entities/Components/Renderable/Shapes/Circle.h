#pragma once

#include <math.h>
#include "Shapes.h"

namespace VoxEngine {
	namespace Graphics {

		class Circle : public Shapes
		{
		public:
			Circle() {}
			Circle(glm::vec3 position, float diameter, float verticesNbr);
			void UpdateShape();

		private:
			float m_Angle;
			float m_Radius;
			GLuint m_VerticesNbr;
		};

	}
}