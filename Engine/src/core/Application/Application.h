#pragma once

#include "Engine.h"

namespace Arcana {

	class Application
	{
	public:
		virtual void Startup() = 0;
		virtual void Run() = 0;
		virtual void Shutdown() = 0;

		void SetShouldRun(bool value) { m_shouldRun = false; }
		bool ShouldRun() { return m_shouldRun; }

		Application* GetInstance() { return s_Instance; }

	protected:
		static Application* s_Instance;

		bool m_shouldRun = true;
	};

	Application* CreateApplication();
}

