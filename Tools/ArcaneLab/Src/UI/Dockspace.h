#pragma once
#include <Engine/UI/DWindow.h>
#include <Engine/Graphics/assets/Texture.h>

namespace ArcanaTools {
	namespace UI {

	class Dockspace : public UIWindow
	{
	public:
		Dockspace():UIWindow("Dockspace") {}
		
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnRender() override;


		
	private:

		void MainMenu();
		bool show_menu = false;
		
		bool m_fullscreen = true;
		ImGuiDockNodeFlags m_dnFlags = ImGuiDockNodeFlags_None;
		Texture2D* play_icon = nullptr;
		Texture2D* stop_icon = nullptr;

	};
	}
}

