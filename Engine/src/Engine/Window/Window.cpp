#include "Window.h"
#include "application/Application.h"

namespace ArcanaTools {
	GLFWwindow* Window::m_window = nullptr;
	bool Window::m_fullscreen = false;
	int Window::m_width		= 0;
	int Window::m_height	= 0;
	EventCallbackFunction Window::EventCallback;
	Window* Window::instance;

	/// <summary>
	/// Requests creation of a GLFWwindow and the address to it
	/// Also assigns glfwsContext to this current window
	/// </summary>
	/// <param name="windowTitle">title to be displayed on the title bar</param>
	/// <param name="viewportWidth">desired width of the viewport</param>
	/// <param name="viewportHeight">desired height of the viewport</param>
	/// <returns>true if window is created false in case it does not</returns>
	bool Window::Create(const char* windowTitle, int viewportWidth, int viewportHeight)
	{
		if (instance != nullptr) // only one window instance at this moment...
			return false;

		m_width = viewportWidth;
		m_height = viewportHeight;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

		//glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
		m_window = glfwCreateWindow(viewportWidth, viewportHeight, windowTitle, nullptr, nullptr);
		
		if(m_window == nullptr)
			return false;
		
		SetFullscreen(false);

		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, instance);
		//glfwSetWindowCloseCallback(m_window, OnWindowClosed);
		glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow * window, int width, int height)
		{
				Window& win = *(Window*)(glfwGetWindowUserPointer(window));
				win.m_width = width;
				win.m_height = height;


				WindowResizeEvent _event(width, height);
				win.EventCallback(_event);
		});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
			{
				Window& win = *(Window*)(glfwGetWindowUserPointer(window));
				glfwSetWindowShouldClose(window, true);
				WindowCloseEvent _event;
				win.EventCallback(_event);
			});
	
		return true;
	}

	bool Window::ShouldClose() { return glfwWindowShouldClose(m_window); }

	GLFWwindow* Window::GetGLFWWindow()
	{
		return m_window;
	}



	void Window::SetEventCallbackFunction(const EventCallbackFunction& callback)
	{
		EventCallback = callback;
	}

	void Window::PollEvents() {
		glfwPollEvents();
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(m_window);
	}


}
