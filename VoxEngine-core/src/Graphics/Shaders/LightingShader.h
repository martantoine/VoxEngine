#include "Shader.h"

namespace VoxEngine
{
	namespace VEGraphics
	{

		class LightingShader : public Shader
		{
		public:
			//Constructors
			LightingShader(const char* vertexShaderPath, const char* FragmentShaderPath);

			//Miscs
			void Init();
		};

	}
}