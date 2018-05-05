#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>

#include "Graphics\Window.h"
#include "Graphics\Shaders\Shader.h"
#include "Graphics\Renderers\SimpleRenderer3D.h"
#include "Graphics\Buffers\Texture.h"

#include "Entities\Entities.h"
#include "Materials\Material.h"

using namespace VoxEngine;
using namespace VEEntity;
using namespace Graphics;
using namespace glm;
using namespace std;

int main()
{


	//Window
	Window window(1920, 1080, "VoxEngine");


	//Lighting
	Entity e_Light;
	PointLight c_Light(vec3(0.0f, -1.0f, 0.0f));
	c_Light.SetParameters(vec3(2.0f, 0.7f, 0.7f), vec3(0.5f, 0.5f, 0.5f), vec3(0.0f, 0.0f, 0.0f));
	e_Light.AddComponent("light 1", c_Light);
	

	//Materials
	Image i_diffuse("diffuse.jpg");
	Texture t_diffuse(i_diffuse);
	Image i_specular("specular.jpg");
	Texture t_specular(i_specular);
	Material material(&t_diffuse, &t_specular, 32.0f);


	//Objects
	///Model
	Entity e_model(vec3(0.0f, 0.0f, 5.0f), 90.0f, vec3(1.0f, 0.0f, 0.0f));
	Model model("nanosuit.obj");
	e_model.AddComponent("nanosuit", model);


	//Camera
	Camera cam(1.5f, 0.0f, 0.0f, 0.0f);
	cam.SetProjection(90.0f, window.GetSize().x / window.GetSize().y);


	//Shader
	Shader LightingShader("src/Graphics/Shaders/BasicLighting.vert", "src/Graphics/Shaders/BasicLighting.frag");
	LightingShader.Bind();
	///Vertex uniforms init
	LightingShader.SetUniformLocation("projection");
	LightingShader.SetUniformLocation("model");
	LightingShader.SetUniformLocation("view");
	///Fragment uniforms 
	LightingShader.SetUniformLocation("texture_diffuse1");
	LightingShader.SetUniformLocation("texture_specular1");
	//LightingShader.SetUniformLocation("material.diffuse");
	//LightingShader.SetUniformLocation("material.specular");
	//LightingShader.SetUniformLocation("material.shininess");
	LightingShader.SetUniformLocation("light.position");
	LightingShader.SetUniformLocation("light.ambient");
	LightingShader.SetUniformLocation("light.diffuse");
	LightingShader.SetUniformLocation("light.specular");
	LightingShader.SetUniformLocation("viewPosition");


	///Vertex uniforms assign
	LightingShader.SetUniformMat4("projection", cam.GetProjection());
	LightingShader.SetUniformMat4("view", cam.GetView());

	///Fragment uniforms assign
	//LightingShader.SetUniform1("material.shininess", material.shininess);
	LightingShader.SetUniform3("light.position", c_Light.GetPosition());
	LightingShader.SetUniform3("light.ambient", c_Light.GetAmbient());
	LightingShader.SetUniform3("light.diffuse", c_Light.GetDiffuse());
	LightingShader.SetUniform3("light.specular", c_Light.GetSpecular());
	LightingShader.SetUniform3("viewPosition", cam.GetPosition());


	//Renderer
	SimpleRenderer3D renderer;
	renderer.LinkShader(LightingShader);

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
			e_model.Move(vec3(0.0f, 0.05f, 0.0f));
		else if (window.GetKey(GLFW_KEY_DOWN))
			e_model.Move(vec3(0.0f, -0.05f, 0.0f));
		if (window.GetKey(GLFW_KEY_RIGHT))
			e_model.Move(vec3(0.05f, 0.0f, 0.0f));
		else if (window.GetKey(GLFW_KEY_LEFT))
			e_model.Move(vec3(-0.05f, 0.0f, 0.0f));
		///Shader
		if (window.GetKey(GLFW_KEY_KP_SUBTRACT))
			material.shininess -= material.shininess / 10.0f;
		else if (window.GetKey(GLFW_KEY_KP_ADD))
			material.shininess += material.shininess / 10.0f;
		else if(window.GetKey(GLFW_KEY_U))
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		else if(window.GetKey(GLFW_KEY_I))
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//LightingShader.SetUniform1("material.shininess", material.shininess);

		///Window
		if (window.GetKey(GLFW_KEY_ESCAPE))
			window.Close();

		//RENDERING
		LightingShader.SetUniformMat4("view", cam.GetView());
		LightingShader.SetUniform3("viewPosition", cam.GetPosition());

		renderer.AddToQueue(e_model);
		renderer.Render();

		window.Update();
	}
	
	return 0;
}