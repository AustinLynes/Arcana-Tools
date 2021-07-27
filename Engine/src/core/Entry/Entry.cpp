#include "Core/Application/Application.h"
#include <Windows.h>

extern Arcana::Application* Arcana::CreateApplication();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR nCmdLine, int nShowCommnad) {
	auto app = Arcana::CreateApplication()->GetInstance();
	app->Startup();
	while (app->ShouldRun())
	{
		app->Run();
	}
	
	app->Shutdown();
	delete app;
	return 0;
}