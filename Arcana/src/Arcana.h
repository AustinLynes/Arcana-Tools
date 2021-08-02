#pragma once

#include "Application/Application.h"
#include "EditorLayer.h"
#include "OutlineLayer.h"

class ArcanaApp : public ArcanaTools::Application {
	virtual bool Initilize() override
	{
		LayerStack::AttachLayer(OutlineLayer::Create("Outlines/"));
		return true;
	}
};

ArcanaTools::Application* ArcanaTools::CreateApplication() {
	return new ArcanaApp();
}

