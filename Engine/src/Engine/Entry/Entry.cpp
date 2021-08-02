#include <application/Application.h>
#include <thread>

#ifdef WIN32

extern ArcanaTools::Application* ArcanaTools::CreateApplication();

int main() {

	auto app = ArcanaTools::CreateApplication();
	if (app != nullptr)
	{
		if (!app->Initilize()) { return -1; }
	
		while (!app->ShouldClose()) {
			
			app->Update();

		}
		app->Shutdown();
	}
	delete app;


	return 0;
}


#else
#error Drengr Engine Only Suports windows.
#endif