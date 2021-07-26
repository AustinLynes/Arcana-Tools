#pragma once

#include "core/Application/Application.h"

namespace Arcana {

	class ArcanaApp : public Application
	{
	public:
		virtual void Startup() override;
		virtual void Run() override;
		virtual void Shutdown() override;
	};
	
	Application* CreateApplication() { return new ArcanaApp(); }
	
}

