#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>

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


using namespace UE;
using namespace UEntity;
using namespace UEGraphics;
using namespace glm;
using namespace std;

int main()
{
	//Window
	Window window(800, 800, "UE");
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Lighting
	Entity e_Light;
	PointLight c_Light(vec3(0.0f, 0.0f, 0.0f));
	c_Light.SetParameters(vec3(0.02f, 0.01f, 0.01f), vec3(0.5f, 0.5f, 0.5f), vec3(0.5f, 0.5f, 0.5f));
	e_Light.AddComponent("light 1", c_Light);

	//Objects
	///Texture
	Image i_d("Assets/fond.png");
	Texture t_d(i_d);
	Image i_s("Assets/specular.jpg");
	Texture t_s(i_s);
	///Materials
	Material m(t_d, t_s, 32);
	///Model
	Entity e_model(vec3(0.0f, 0.0f, 0.0f), 90.0f, vec3(1.0f, 0.0f, 0.0f));
	Model model("Assets/nanosuit.obj");
	model.SetScale(vec3(0.1f, 0.1f, 0.1f));
	e_model.AddComponent("nanosuit", model);
	///Text
	Font font("fonts/arial.ttf", 32);
	Text text(font, "Text rendered with opengl", vec3(-0.5f, -0.5f, 0.0f), 0.003f);

	///Plane
	Entity e_plane;
	Rectangle c_plane(vec3(-1.0f, -1.0f, 0.0f), vec2(2.0f, 2.0f), 0.0f, vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f));
	c_plane.AddMaterial(m);
	c_plane.AddTexture(MATERIAL_TEXTURE::DIFFUSE);

	e_plane.AddComponent("plane", c_plane);

	//Camera
	Camera cam(1.5f, 0.0f, 0.0f, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	cam.SetProjection(70.0f, window.GetSize().x / window.GetSize().y);

	//Shader
	LightingShader shader("src/Graphics/Shaders/BasicLighting.vert", "src/Graphics/Shaders/BasicLighting.frag");
	shader.Bind();
	shader.SetUniformMat4("projection", cam.GetProjection());
	shader.SetUniform3("light.position", c_Light.GetPosition());
	shader.SetUniform3("light.ambient", c_Light.GetAmbient());
	shader.SetUniform3("light.diffuse", c_Light.GetDiffuse());
	shader.SetUniform3("light.specular", c_Light.GetSpecular());

	//Renderer
	SimpleRenderer3D renderer1;
	renderer1.LinkShader(shader);
	SimpleRenderer2D renderer2;
	renderer2.LinkShader(shader);

	while (window.Closed())
	{
		window.Clear();
		//EVENTS MANAGING
		///Camera
		cam.SetMousePos(window.GetMousePos());
		cam.Zoom(window.GetScrollOffset());
		if (window.GetKey(GLFW_KEY_C))
			cam.Reset();
		if (window.GetButton(GLFW_MOUSE_BUTTON_RIGHT))
		{
			cam.Rotate();
			glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else if (window.GetButton(GLFW_MOUSE_BUTTON_MIDDLE))
		{
			cam.Move();
			shader.SetUniformMat4("projection", cam.GetProjection());
			glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else
			glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		///Model
		if (window.GetKey(GLFW_KEY_UP))
			e_plane.Move(vec3(0.0f, 0.05f, 0.0f));
		else if (window.GetKey(GLFW_KEY_DOWN))
			e_plane.Move(vec3(0.0f, -0.05f, 0.0f));
		if (window.GetKey(GLFW_KEY_RIGHT))
			e_plane.Move(vec3(0.05f, 0.0f, 0.0f));
		else if (window.GetKey(GLFW_KEY_LEFT))
			e_plane.Move(vec3(-0.05f, 0.0f, 0.0f));
		///Shader
		else if(window.GetKey(GLFW_KEY_U))
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else if(window.GetKey(GLFW_KEY_I))
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		///Window
		if (window.GetKey(GLFW_KEY_ESCAPE))
			window.Close();

		//RENDERING
		shader.SetUniformMat4("view", cam.GetView());
		shader.SetUniform3("viewPosition", cam.GetPosition());

		renderer1.AddToQueue(e_model);
		renderer1.Render();
		renderer2.AddToQueue(e_plane);
		renderer2.Render();
		text.Draw(shader);
		window.Update();
	}
	
	return 0;
}