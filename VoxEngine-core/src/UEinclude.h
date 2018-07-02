#define STB_IMAGE_IMPLEMENTATION

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <GLM\glm.hpp>

#include "Graphics\Window.h"
#include "Graphics\Shaders\Shader.h"
#include "Graphics\Renderers\SimpleRenderer2D.h"
#include "Graphics\Renderers\SimpleRenderer3D.h"
#include "Graphics\Buffers\Texture.h"

#include "Entities\Components\Renderable\Shapes\Text.h"
#include "Graphics\Shaders\LightingShader.h"
#include "Entities\Entities.h"
#include "Materials\Material.h"

#include "Entities\Components\Renderable\Shapes\Font.h"
#include "Entities\Components\Renderable\Shapes\Text.h"

using namespace UE::UEntity;
using namespace UE;
using namespace UEntity;
using namespace UEGraphics;
using namespace glm;