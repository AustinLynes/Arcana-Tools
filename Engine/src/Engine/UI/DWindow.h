#pragma once


#include <Platform/ImGui/ImGuiBuild.h>

#include <string>
#include <vector>

/*
	A Docking Window is the wrapper class
	for a normal ImGui::Begin call

	The Structure for D<GUI> classes
	[DWindow]
		|
		+----[DChild]----[...]
				|
				+----[DGroup]----[...]
				|		|
				|		+--------[DItem]----[...]
				|		
				+----[DTabGroup]----[...]
						|
						+--------[DItem]----[...]
*/


namespace ArcanaTools {

	namespace UI {

		class UIWindow
		{
		public:
			UIWindow(const std::string& tag) : m_show(true), m_tag(tag) {}
			virtual ~UIWindow() {}

			virtual void OnAttach() = 0;
			virtual void OnDetach() = 0;
			virtual void OnUpdate() = 0;
			virtual void OnRender();

			const std::string& GetTag();

			bool Begin(const char* title);
			void End();

		protected:
			std::string m_tag;

			bool m_show;
			ImGuiWindowFlags m_flags = 0;
			ImGuiDockNodeFlags m_dnflags = 0;
			ImGuiWindowClass m_class;


		};

	}

}

