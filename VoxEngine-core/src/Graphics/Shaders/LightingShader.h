#include "Shader.h"

namespace UE
{
	namespace UEGraphics
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