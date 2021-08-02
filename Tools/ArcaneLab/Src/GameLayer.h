#pragma once
#include <Engine/layers/Layer.h>
#include <Engine/Graphics/buffers/Framebuffer.h>
#include "UI/GameViewport.h"

namespace ArcanaTools {

	class GameLayer : public Layer
	{
	public:
		GameLayer() : Layer("GameLayer") {};
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(TimeStep ts) override;
		virtual void OnEvent(Event& _event) override;
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;

		static Framebuffer* GetFrameBuffer() { return m_FrameBuffer; }
	private:
		static Framebuffer* m_FrameBuffer;
		UI::GameViewport* m_viewport;

	};
}

