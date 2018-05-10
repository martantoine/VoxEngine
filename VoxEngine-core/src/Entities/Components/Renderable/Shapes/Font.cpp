#include "Font.h"

namespace UE
{
	namespace UEntity
	{

		//--------------------------------------------------------------------------------//
		//**********************************Constructors**********************************//
		//--------------------------------------------------------------------------------//
		Font::Font()
		{
		}

		Font::Font(const char* path, int pixelSize)
		{
			Init(path, pixelSize);
		}



		//--------------------------------------------------------------------------------//
		//***********************************Initialize***********************************//
		//--------------------------------------------------------------------------------//
		void Font::Init(const char* path, int pixelSize)
		{
			FT_Library ft;
			if (FT_Init_FreeType(&ft))
				std::cout << "ERROR::FREETYPE:Could not init FreeType Library" << std::endl;

			FT_Face face;
			if (FT_New_Face(ft, path, 0, &face))
				std::cout << "ERROR::FREETYPE:Failed to load the font " << path << std::endl;

			FT_Set_Pixel_Sizes(face, pixelSize, pixelSize);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction


			for (GLubyte c = 0; c < 128; c++) //128 because it's enough !
			{
				// Load character glyph 
				if (FT_Load_Char(face, c, FT_LOAD_RENDER))
				{
					std::cout << "ERROR::FREETYTPE:Failed to load Glyph" << std::endl;
					continue;
				}

				//Create the character
				Character character;
				character.Size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
				character.Bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
				character.Advance = face->glyph->advance.x;

				//Generate the texture
				GLuint& texture = character.TextureID;
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					face->glyph->bitmap.width,
					face->glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					face->glyph->bitmap.buffer
				);
				///Set the texture options
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

				//Store the character
				m_Characters.insert(std::pair<GLchar, Character>(c, character));
			}
			FT_Done_Face(face);
			FT_Done_FreeType(ft);
		}



		//--------------------------------------------------------------------------------//
		//**********************************Get function**********************************//
		//--------------------------------------------------------------------------------//
		Character Font::GetChar(GLchar character)
		{
			return m_Characters[character];
		}

	}
}