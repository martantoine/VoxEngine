#include "Shader.h"

namespace VoxEngine
{
	namespace Graphics
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