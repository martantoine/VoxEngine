#include "Window.h"

namespace VoxEngine {
	namespace Graphics {

		void window_size_callback(GLFWwindow* window, int width, int height);
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void mouse_cursorpos_callback(GLFWwindow* window, double xpos, double ypos);
		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

		int Window::mx = mx;
		int Window::my = my;
		bool Window::keys[1024] = { 0 };
		bool Window::mouseButtons[16] = { 0 };
		double Window::mouseScrollOffsetY = mouseScrollOffsetY;

		Window::Window()
		{
			m_Width = 0;
			m_Height = 0;
		}

		Window::Window(int width, int height, const char* title)
		{
			CreateWindow(width, height, title);
		}

		void Window::CreateWindow(int width, int height, const char* title)
		{
			m_Width = width;
			m_Height = height;
			mouseScrollOffsetY = 0.0;

			glfwInit();
			m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
			MakeCurrent();
			glfwSetWindowSizeCallback(m_Window, window_size_callback);
			glfwSetKeyCallback(m_Window, key_callback);
			glfwSetCursorPosCallback(m_Window, mouse_cursorpos_callback);
			glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
			glfwSetScrollCallback(m_Window, mouse_scroll_callback);
			glfwSwapInterval(1);
			glewInit();
			glEnable(GL_DEPTH_TEST);
			glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
			glfwSetCursorPos(m_Window, 0.0f, 0.0f);
		
			m_LastTime = glfwGetTime();
			m_Frame = 0;
		}

		void Window::MakeCurrent()
		{
			glfwMakeContextCurrent(m_Window);
		}

		bool Window::Closed()
		{
			return !glfwWindowShouldClose(m_Window);
		}

		void Window::Clear()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::Update()
		{
			double currentTime = glfwGetTime();
			m_Frame++;
			if (currentTime - m_LastTime > 1.0)//Use cout fonction every seconds
			{
				std::cout << "Delta time = " << static_cast<double>(1000.0f / m_Frame) << " ms\n";
				m_Frame = 0;
				m_LastTime = currentTime;
			}

			mouseScrollOffsetY = 0.0;
			glfwSwapBuffers(m_Window);
			glfwPollEvents();
		}

		bool Window::GetKey(int key)
		{
			return keys[key];
		}

		bool Window::GetButton(int button)
		{
			return mouseButtons[button];
		}

		glm::vec2 Window::GetMousePos()
		{
			return glm::vec2(mx, my);
		}

		glm::vec2 Window::GetSize()
		{
			return glm::vec2(m_Width, m_Height);
		}

		double Window::GetScrollOffset()
		{
			return static_cast<double>(mouseScrollOffsetY);
		}

		void Window::Close()
		{
			glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
		}

		Window::~Window()
		{
			glfwDestroyWindow(m_Window);
			glfwTerminate();
		}

		void window_size_callback(GLFWwindow* window, int width, int height)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			glViewport(0, 0, width, height);
		}

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			//action : GLFW_PRESS, GLFW_REPEAT, GLFW_RELEASE
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->keys[key] = action != GLFW_RELEASE;

		}

		void mouse_cursorpos_callback(GLFWwindow* window, double xpos, double ypos)
		{
			Window* win = (Window*) glfwGetWindowUserPointer(window);
			win->mx = static_cast<int>(xpos);
			win->my = static_cast<int>(ypos);
		}

		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->mouseButtons[button] = action != GLFW_RELEASE;
		}

		void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->mouseScrollOffsetY = yoffset;
		}

	}
}