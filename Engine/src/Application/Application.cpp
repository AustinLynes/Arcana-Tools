#include "Application.h"
#include <thread>
#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
namespace ArcanaTools {
	
	bool Application::m_minimized = false;

	//using namespace Components;
	Application::Application(const char* engineTitle) {

		if (glfwInit() == GLFW_FALSE)
			return;

		m_info.title = engineTitle;
		m_info.version.major = 1;
		m_info.version.minor = 0;
		m_info.version.patch = 0;


		Window::SetEventCallbackFunction(BIND_EVENT_FN(Application::OnEvent));

		//// create the window
		if (!Window::Create(m_info.title, 1280, 720)) {
			return;
		}

		// initilize GLAD and load function pointers

		if (!gladLoadGL()) {
			std::cout << "Could Not initilize GLAD" << std::endl;
			return;
		}



		Renderer3D::Init();

		m_gui = new ImGuiLayer();
		LayerStack::AttachOverlay(m_gui);

	}
	Application::~Application() {}

	bool Application::ShouldClose() { return Window::ShouldClose(); }
	void Application::Update()
	{

		float time = (float)glfwGetTime();
		TimeStep ts = time - last_frametime;

		if (!m_minimized) {

			if (Window::ShouldClose()) {
				return;
			}

			Window::PollEvents();

			if (ts >= 1 / 120 * 1000.0f)
			{
				last_frametime = time;
				LayerStack::UpdateLayers(ts);
			}

			m_gui->Begin();
			LayerStack::RenderGUILayers();
			m_gui->End();


			LayerStack::RenderLayers();

			Window::SwapBuffers();
		}


	}
	void Application::OnEvent(Event& _event)
	{
		EventDispatcher dispatcher(_event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

		LayerStack::OnEvent(_event);

	}
	bool Application::OnWindowClose(Event& _event)
	{
		std::cout << "HEY THERE" << std::endl;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& _event)
	{
		if (_event.GetWidth() == 0 || _event.GetHeight() == 0)
		{
			m_minimized = true;
			return false;
		}
		m_minimized = false;

		return true;
	}

	void Application::Shutdown()
	{
		LayerStack::Cleanup();
	}

}