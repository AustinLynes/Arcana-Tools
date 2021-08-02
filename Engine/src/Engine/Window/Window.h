#pragma once
// will be moved to the renderer layer or one of the renderer components
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include "Engine/Event/Event.h"

namespace ArcanaTools {

	using EventCallbackFunction = std::function<void(Event&)>;
	class Window
	{
	public:
		Window() {};
		~Window() { glfwDestroyWindow(m_window); };

		static bool Create(const char* windowTitle, int viewportWidth, int viewportHeight);
		static void SwapBuffers();
		static void PollEvents();
		static bool ShouldClose();


		static GLFWwindow* GetGLFWWindow();
		static Window* instance;
		static void SetEventCallbackFunction(const EventCallbackFunction& callback);
		static int GetWidth() { return m_width; }
		static int GetHeight() { return m_height; }

		static bool GetFullScreen() { return m_fullscreen; }
		static void SetFullscreen(bool value) {
			m_fullscreen = value;
			if (m_fullscreen)
				glfwMaximizeWindow(m_window);
		}
	private:
		static int m_width;
		static int m_height;

		static bool m_fullscreen;

		static GLFWwindow* m_window;
		static EventCallbackFunction EventCallback;


	};
}

