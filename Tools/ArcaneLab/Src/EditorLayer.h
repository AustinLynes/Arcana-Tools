#pragma once
// engine includes 
#include <Engine/Graphics/renderers/Renderer3D.h>
#include <Engine/Graphics/buffers/Framebuffer.h>

#include <Engine/layers/Layer.h>


// ECS
#include <Engine/Scene/Scene.h>
#include <Engine/ECS/Components/DefaultComponents.h>

// HID
#include <Engine/Input/Input.h>

// editor includes
#include "UI/Panels.h"

// editor viewport camera
//#include "EditorCamera.h"

using namespace ArcanaTools;
using namespace ArcanaTools::UI;

class EditorLayer : public Layer
{
public:
	EditorLayer() : Layer("editor"){}

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(TimeStep ts) override;
	virtual void OnEvent(Event& _event) override;
	virtual void OnImGuiRender() override;

	virtual void OnRender() override;
	
	static Framebuffer* GetFrameBuffer() { return m_FrameBuffer; };
	static Entity* GetCamera() { return camera; }

private:

	std::vector<UIWindow*> m_ui;


	static Framebuffer* m_FrameBuffer;
	static Entity* camera;
	
	bool first = true;
	bool wireframe = false;

	glm::vec2 last_rot;

	float sensitivity = 0.1f;

};

