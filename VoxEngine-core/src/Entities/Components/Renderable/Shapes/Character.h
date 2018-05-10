#pragma once

#include <GL\glew.h>
#include <GLM\vec2.hpp>

namespace UE
{
	namespace UEntity
	{

		struct Character
		{
			GLuint TextureID;
			glm::vec2 Size;
			glm::vec2 Bearing; //Bearing is the offset between the origin and top left hand corner of the glych
			GLuint Advance; //Advance is the distance between two consecutivs origins
		};
	}
}