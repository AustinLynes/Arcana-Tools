#pragma once
#include "Engine/UI/DWindow.h"
#include <filesystem>

namespace ArcanaTools {
	using namespace UI;

	class SetupWindow : public UIWindow
	{
	public:
		SetupWindow() : UIWindow("Welcome") {};
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnRender() override;


		void LeftPanel();
		void RightPanel();
		bool Modal();
		
	private:
		std::string prj_name = "";
		std::string prj_dir = "";
		int selected_api = 0;
		int selected_pipeline = 0;
		bool m_shouldClose = false;
	};
};

