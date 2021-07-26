#pragma once

#include "Engine.h"

namespace Arcana {

	class Application
	{
	public:
		virtual void Startup() = 0;
		virtual void Run() = 0;
		virtual void Shutdown() = 0;

	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
}

