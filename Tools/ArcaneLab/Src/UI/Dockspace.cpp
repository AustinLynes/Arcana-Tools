#include "Dockspace.h"

#include "../EditorLayer.h"
#include <Engine/Scene/SceneSerializer.h>
#include "Engine/Utils/PlatformUtils.h"
#include "Engine/Window/Window.h"
#include "../OutlineLayer.h"

namespace ArcanaTools {
	namespace UI {
		
		void Dockspace::OnAttach()
		{
			play_icon = Texture2D::Create("resources/icons/play.png");
			stop_icon = Texture2D::Create("resources/icons/stop.png");
		}

		void Dockspace::OnDetach()
		{
		}

		void Dockspace::OnUpdate()
		{

		}

		void Dockspace::OnRender()
		{
			if (m_show) {

				int clrCount = 0;
				int varCount = 0;

				static bool opt_fullscreen_persistant = true;
				m_fullscreen = opt_fullscreen_persistant;

				m_dnFlags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_NoWindowMenuButton ;

				m_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;

				if (m_fullscreen) {
					ImGuiViewport* vp = ImGui::GetMainViewport();
					ImGui::SetNextWindowPos(vp->Pos);
					ImGui::SetNextWindowSize(vp->Size);
					ImGui::SetNextWindowViewport(vp->ID);
					ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f); varCount++;
					ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f); varCount++;
					m_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
					m_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
				}

				if (m_dnFlags & ImGuiDockNodeFlags_PassthruCentralNode) {
					m_flags |= ImGuiWindowFlags_NoBackground;
				}


				if (m_fullscreen) {
					int c = 0;
					for (size_t i = 0; i < varCount; i++)
					{
						ImGui::PopStyleVar();
						c++;
					}
					varCount -= c;
				}
				show_menu = true;
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f)); varCount++;
				
				if (show_menu)
					m_flags |= ImGuiWindowFlags_MenuBar;

				if (!Begin("###DockSpace")) {
					return;
				}

				if(show_menu)
					MainMenu();
				

				ImGuiIO& io = ImGui::GetIO();
				io.ConfigWindowsMoveFromTitleBarOnly = true;

				if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
				{
					ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
					ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), m_dnFlags);
				}

			
				ImGui::PopStyleVar(varCount);
				ImGui::PopStyleColor(clrCount);
				ImGui::End();
			}

		}
		void Dockspace::MainMenu()
		{
			int clrCount = 0;
			int varCount = 0;
			
			//m_flags |= ImGuiWindowFlags_MenuBar;

			ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, { 0.0f, 0.0f }); varCount++;
			ImGui::PushStyleVar(ImGuiStyleVar_PopupRounding, 0.0f); varCount++;
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 10.0f, 15.0f }); varCount++;;

			if (ImGui::BeginMenuBar()) {

				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("New", "Ctrl+N")) {
						OutlineLayer::NewScene("DEFAULT");// :: FIX ME
					}
					if (ImGui::MenuItem("Open", "Ctrl+O")) {
						OutlineLayer::OpenScene("");

					}
					if (ImGui::MenuItem("Save", "Ctrl+S")) {
						OutlineLayer::SaveScene();

					}
					if (ImGui::MenuItem("Save As", "Ctrl+Shift+S")) {
						OutlineLayer::SaveSceneAs();
					}

					ImGui::Separator();

					if (ImGui::MenuItem("Exit", "Alt+F4")) {
						glfwSetWindowShouldClose(Window::GetGLFWWindow(), true);
					}

					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("View"))
				{

					/*if (ImGui::BeginMenu("Viewports")) {
						if (ImGui::MenuItem("Editor")) {
							auto editor_viewport = new EditorViewport();
							Panels[editor_viewport->GetTag().c_str()] = editor_viewport;
						}
						ImGui::EndMenu();
					}

					if (ImGui::MenuItem("Properties")) {
						auto properties_panel = new PropertiesPanel();
						Panels[properties_panel->GetTag().c_str()] = properties_panel;

					}
					if (ImGui::MenuItem("Console")) {
						auto console_window = new ConsoleWindow();
						Panels[console_window->GetTag().c_str()] = console_window;

					}*/

					ImGui::EndMenu();
				}
				
				
				ImGui::PopStyleVar(varCount);
				ImGui::PopStyleColor(clrCount);

				ImGui::EndMenuBar();
			}

			// MOVE TO ANOTHER UI THING?? MAYBE IT SHOULD BE A STATIC MENUBAR?
			// REALTIME FUNCTIONS CONSIST OF 
			// PLAY / STOP FUNCTIONALITY FOR THE EDITOR AND GAME VIEWPORTS
			if (OutlineLayer::ShouldAllowRealtimeFunctions()) {
				if (ImGui::BeginChild("###RuntimeFunctions", { ImGui::GetContentRegionAvail().x , 36 })) {

					float size = 16;
					float halfwidth = ImGui::GetContentRegionAvail().x / 2.0f;
					float drawPos = halfwidth - size;
					ImGui::SetCursorPosX(halfwidth);

					bool is_runtime = OutlineLayer::GetActiveScene()->ShouldPlay();
					ImTextureID id = is_runtime ? (ImTextureID)stop_icon->GetTextureID() : (ImTextureID)play_icon->GetTextureID();

					if (ImGui::ImageButton((void*)id, { size, size })) {
						if (is_runtime) {
							OutlineLayer::GetActiveScene()->OnRuntimeExit();
						}
						else {
							OutlineLayer::GetActiveScene()->OnRuntimeStart();
						}
					}

					ImGui::EndChild();
				}
			}
		}
	}



	//void Dockspace::NewScene() {
	///*	EditorLayer::DeleteScene();
	//	auto newScene = new Scene();
	//	EditorLayer::ActiveScene = newScene;*/
	//}
	//void Dockspace::SaveScene() {

	//}
	//void Dockspace::SaveSceneAs() {
	//	std::optional<std::string> filepath = Utils::FileDialog::SaveFile("Drengr Scene (*.drengr)\0*.drengr\0");
	//	if (filepath) {
	//		auto scene = EditorLayer::ActiveScene;

	//		SceneSerializer ser(scene);
	//		ser.Serialize(*filepath);
	//	}
	//}

	//void Dockspace::OpenScene() {
	//	std::optional<std::string> filepath = Utils::FileDialog::OpenFile("Drengr Scene (*.drengr)\0*.drengr\0");
	//	if (filepath) {
	//		NewScene();
	//		auto scene = EditorLayer::ActiveScene;
	//		SceneSerializer ser(scene);
	//		ser.Deserialize(*filepath);

	//		EditorLayer::ActiveScene->Initilize();
	//	}
	//}

}
