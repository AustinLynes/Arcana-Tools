#include "ArcanaApp.h"
#include "core/Debugging/Logger.h"


namespace Arcana {

	void ArcanaApp::Startup()
	{
		Logger::Log("Application Startup.");
	}

	void ArcanaApp::Run()
	{
		Logger::Flush();
	}

	void ArcanaApp::Shutdown()
	{
	}
}
