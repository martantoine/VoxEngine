#include "Shader.h"
#include "../../Entities/Components/Lights/PointLight.h"
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
			void SetLight(UEntity::PointLight& light);
		};

	}
}