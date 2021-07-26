#include "Core/Application/Application.h"

extern Arcana::Application* Arcana::CreateApplication();

int main() {
	auto app = Arcana::CreateApplication();
	app->Startup();
	app->Run();
	app->Shutdown();
	delete app;
	return 0;
}