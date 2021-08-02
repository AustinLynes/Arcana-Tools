#pragma once
#include <engine/window/Window.h>

#include "engine/layers/LayerStack.h"

#include <engine/graphics/renderers/Renderer3D.h>
//#include "Engine/ECS/GameObject.h"

#include <Engine/Time/TimeStep.h>
//#include <Engine/Event/Event.h>
#include "Engine/Event/ApplicationEvents.h"
#include "Engine/layers/engine/ImGuiLayer.h"

namespace ArcanaTools {

	struct EngineInfo {
		const char* title;
		struct {
			int major;
			int minor;
			int patch;
		}version;
	};


	class Application
	{
	public:
		Application(const char* engineTitle="Drengr Engine");
		virtual ~Application();
		virtual bool Initilize() = 0;
		virtual void Update();
		virtual void Shutdown();

		virtual void OnEvent(Event& _event);
		virtual bool OnWindowClose(Event& _event);
		virtual bool OnWindowResize(WindowResizeEvent& _event);
		bool ShouldClose();
	
	protected:
		EngineInfo m_info;
		ImGuiLayer* m_gui;

		float last_frametime = 0.0f;
		static bool m_minimized;
	};

	Application* CreateApplication();

	

}
