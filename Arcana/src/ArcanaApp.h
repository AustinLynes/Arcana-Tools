#pragma once

#include "core/Application/Application.h"

namespace Arcana {

	class ArcanaApp : public Application
	{
	public:
		virtual void Startup() override;
		virtual void Run() override;
		virtual void Shutdown() override;

		static Application* CreateInstance() { 

			if (s_Instance != nullptr) {
				return nullptr;
			}
	
			s_Instance = new ArcanaApp();
		}
	};
	
	Application* CreateApplication() { return ArcanaApp::CreateInstance(); }
	
}

