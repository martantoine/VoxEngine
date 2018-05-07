#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>

#include "Graphics\Window.h"
#include "Graphics\Shaders\LightingShader.h"
#include "Graphics\Renderers\SimpleRenderer3D.h"
#include "Graphics\Buffers\Texture.h"

#include "Entities\Entities.h"
#include "Materials\Material.h"

using namespace VoxEngine;
using namespace VEEntity;
using namespace VEGraphics;
using namespace glm;
using namespace std;

int main()
{
	//Window
	Window window(1920, 1080, "VoxEngine");

	//Lighting
	Entity e_Light;
	PointLight c_Light;
	c_Light.SetParameters(vec3(0.0f, 0.0f, 0.0f), vec3(0.9f, 0.95f, 0.8f), vec3(1.0f, 1.0f, 1.0f));
	e_Light.AddComponent("light 1", c_Light);

	//Objects
	///Model
	Entity e_model(vec3(0.0f, 0.0f, 0.0f), 90.0f, vec3(1.0f, 0.0f, 0.0f));
	Model model("bouche.stl");
	model.SetScale(vec3(0.01f, 0.01f, 0.01f));
	e_model.AddComponent("nanosuit", model);

	///Plane
	//Entity e_plane;
	//Rectangle c_plane;

	//Camera
	Camera cam(1.5f, -90.0f, 0.0f, 0.0f);
	cam.SetProjection(90.0f, window.GetSize().x / window.GetSize().y);

	//Shader
	LightingShader shader("src/VEGraphics/Shaders/BasicLighting.vert", "src/VEGraphics/Shaders/BasicLighting.frag");
	shader.SetUniformMat4("projection", cam.GetProjection());
	shader.SetUniform3("light.position", c_Light.GetPosition());
	shader.SetUniform3("light.ambient", c_Light.GetAmbient());
	shader.SetUniform3("light.diffuse", c_Light.GetDiffuse());
	shader.SetUniform3("light.specular", c_Light.GetSpecular());

	//Renderer
	SimpleRenderer3D renderer;
	renderer.LinkShader(shader);

	float explosion(500.0f);
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
			glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else
			glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		///Model
		if (window.GetKey(GLFW_KEY_UP))
			explosion *= 1.1f;
		else if (window.GetKey(GLFW_KEY_DOWN))
			explosion /= 1.1f;
		if (explosion < 1.0f)
			explosion = 1.0f;
		///Shader
		else if (window.GetKey(GLFW_KEY_U))
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else if (window.GetKey(GLFW_KEY_I))
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		///Window
		if (window.GetKey(GLFW_KEY_ESCAPE))
			window.Close();

		//Shader
		shader.SetUniform1("explosion", explosion);
		shader.SetUniformMat4("view", cam.GetView());
		shader.SetUniform3("viewPosition", cam.GetPosition());

		//Rendering
		renderer.AddToQueue(e_model);
		renderer.Render();

		if (explosion > 1.0)
			explosion /= 1.02f;
		else
			explosion = 1.0f;
		window.Update();

	}
	
	return 0;
}