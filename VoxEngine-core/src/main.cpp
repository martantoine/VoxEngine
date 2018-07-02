#include "UEinclude.h"

int main()
{
	//Window
	Window window(800, 800, "UE");

	//Lighting
	PointLight c_light(vec3(0.0f));
	c_light.SetLightParameters(vec3(0.02f, 0.01f, 0.01f), vec3(0.5f), vec3(0.5f));
	Entity e_light("light", c_light);
	
	//Model
	Model c_model("Assets/nanosuit.obj");
	c_model.SetScale(vec3(0.1f));
	Entity e_model(vec3(0.0f), 90.0f, vec3(1.0f, 0.0f, 0.0f));
	e_model.AddComponent("nanosuit", c_model);

	//Text
	Font font("fonts/arial.ttf", 32);
	Text text(font, "Text rendered with opengl", vec3(-0.5f, -0.5f, 0.0f), 0.003f);

	//Material
	Texture t_UI(new Image("Assets/fond.png"));
	Material m_UI(t_UI, t_UI, 32);

	//Plane
	Rectangle c_UI(vec3(-1.0f, -1.0f, 0.0f), vec2(2.0f, 2.0f), 0.0f, vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f));
	c_UI.AddMaterial(m_UI);
	Entity e_UI("UI", c_UI);

	//Camera
	Camera cam(1.5f, 0.0f, 0.0f, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	cam.SetProjection(70.0f, window.GetSize().x / window.GetSize().y);

	//Shader
	LightingShader shader("src/Graphics/Shaders/BasicLighting.vert", "src/Graphics/Shaders/BasicLighting.frag");
	shader.SetUniformMat4("projection", cam.GetProjection());
	shader.SetLight(c_light);

	//Renderer
	SimpleRenderer3D renderer1(shader);
	SimpleRenderer2D renderer2(shader);

	while (window.Closed())
	{
		//EVENTS MANAGING
		cam.SetMousePos(window.GetMousePos());
		cam.Zoom(window.GetScrollOffset());
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
		shader.SetUniformMat4("view", cam.GetView());
		shader.SetUniform3("viewPosition", cam.GetPosition());

		//Rendering
		window.Clear();
		renderer1.Render(e_model);
		renderer2.Render(e_UI);
		text.Draw(shader);
		window.Update();
	}
	
	return 0;
}