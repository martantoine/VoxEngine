#pragma once

#ifdef UE_EMSCRIPTEN
	#define GLFW_INCLUDE_ES3
	#include <GLES3/gl3.h>
	#include <GLFW/glfw3.h>
#else
	#include <GL/glew.h>
	#include <GLFW/glfw3.h>
#endif

#include <stdio.h>
#include <iostream>
#include <GLM\vec2.hpp>

namespace UE
{
	namespace UEGraphics
	{

		class Window
		{
		public:
			Window();
			Window(int width, int height, const char* title);
			void CreateWindow(int width, int height, const char* title);
			void MakeCurrent();
			
			bool Closed();
			void Clear();
			void Update();
			
			bool GetKey(int key);
			bool* GetKeys();
			bool GetButton(int button);
			double GetScrollOffset();

			glm::vec2 GetMousePos();
			glm::vec2 GetSize();
			GLFWwindow* GetWindow() const { return m_Window; }
			void Close();
			~Window();

		private:
			void friend window_size_callback(GLFWwindow* window, int width, int height);
			friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend void mouse_cursorpos_callback(GLFWwindow* window, double xpos, double ypos);
			friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			friend void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

		private:
			GLFWwindow* m_Window;
			unsigned int m_Frame;
			int m_Width, m_Height;
			double m_LastTime;

			static int mx, my;
			static bool keys[1024];
			static bool mouseButtons[16];
			static double mouseScrollOffsetY;
		};

	}
}