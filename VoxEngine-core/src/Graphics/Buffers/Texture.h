#pragma once

#include <GL\glew.h>
#include "../Buffers/Image.h"
#include <string>

namespace VoxEngine
{
	namespace Graphics
	{

		class Texture
		{
		public:
			Texture() {}
			Texture(Image& image);
			void SetID(Image& image);

			unsigned int GetID() { return *m_Texture; }
			void SetType(std::string type) { m_Type = type; }
			void SetPath(std::string path) { m_Path = path; }

			std::string GetName() { return m_Path; }
			std::string GetType() { return m_Type; }

			void Bind();
			void Unbind();
			
			int GetWidth() { return m_Image->width; }
			int GetHeight() { return m_Image->height; }

		private:
			GLuint* m_Texture;
			Image* m_Image;

			std::string m_Type;
			std::string m_Path;
		};

	}
}