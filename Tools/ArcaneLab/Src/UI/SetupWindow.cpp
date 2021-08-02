#include "SetupWindow.h"
#include "../OutlineLayer.h"
namespace ArcanaTools {
	void SetupWindow::OnAttach()
	{
		prj_dir = "Projects/" + prj_dir;
	}

	void SetupWindow::OnDetach()
	{
	}

	void SetupWindow::OnUpdate()
	{
	}




	void SetupWindow::OnRender()
	{

		int clrCount = 0;
		int varCount = 0;
		if (m_show) {

			m_flags = ImGuiWindowFlags_NoMove;
			m_dnflags = ImGuiDockNodeFlags_NoCloseButton | ImGuiDockNodeFlags_NoWindowMenuButton | ImGuiDockNodeFlags_HiddenTabBar;

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0,0 }); varCount++;

			//ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 0,0 }); varCount++;


			if (!Begin("Welcome to Acrana Tools!")) {
				return;
			}

			ImGui::PopStyleColor(clrCount);
			clrCount -= clrCount;
			ImGui::PopStyleVar(varCount);
			varCount -= varCount;

			LeftPanel();
			ImGui::SameLine();
			RightPanel();

			End();

		}



	}
	void SetupWindow::LeftPanel()
	{
		int clrCount = 0;
		int varCount = 0;
		ImGui::PushStyleColor(ImGuiCol_ChildBg, { 0.21,0.21,0.21,1.0f }); clrCount++;
		ImGui::PushStyleColor(ImGuiCol_Border, { 0.21,0.21,0.21,1.0f }); clrCount++;
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0,0 }); varCount++;


		ImVec2 leftSize = ImGui::GetContentRegionAvail();
		if (ImGui::BeginChild("##Left", ImVec2(leftSize.x * 0.18, leftSize.y), true, ImGuiWindowFlags_AlwaysUseWindowPadding)) {


			ImGui::EndChild();
		}

		ImGui::PopStyleColor(clrCount);
		ImGui::PopStyleVar(varCount);

	}
	void SetupWindow::RightPanel()
	{

		ImVec2 rightSize = ImGui::GetContentRegionAvail();
		int clrCount = 0;
		int varCount = 0;

		ImGui::PushStyleColor(ImGuiCol_Border, { 0.21,0.21,0.21,1.0f }); clrCount++;
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0,0 }); varCount++;

		if (ImGui::BeginChild("##Right", rightSize, true, ImGuiWindowFlags_AlwaysUseWindowPadding)) {

				if (ImGui::Button("New Project")) {
					ImGui::OpenPopup("New Project");
				}

				Modal();

				ImVec2 childSize = ImGui::GetContentRegionAvail();

				if (ImGui::BeginChild("###Projects", childSize, false, ImGuiWindowFlags_AlwaysUseWindowPadding)) {
					ImVec2 listbox_size = ImGui::GetContentRegionAvail();

					if (ImGui::BeginListBox("###ProjectsList", listbox_size)) {

						for (auto& path : std::filesystem::directory_iterator("Outlines"))
						{
							if (path.is_directory()) {
								ImGui::BeginGroup();
								{
									ImGui::Image(0, { 64, 64 });
									ImGui::SameLine();

									ImGui::BeginGroup();
									{
										ImGui::Text("Project Name:");
										ImGui::SameLine();
										ImGui::Text("%s", path.path().stem().string().c_str());
										ImGui::EndGroup();
									}

									ImGui::SameLine();
									ImGui::PushID(path.path().stem().string().c_str());

									ImGui::SetCursorPosX(listbox_size.x - 100);
									ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0x7C, 0x4E, 0xFF, 0xFF));
									ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(0x85, 0x6E, 0xFF, 0xFF));
									ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(0x6C, 0x3E, 0xFF, 0xFF));

									if (ImGui::Button("Open")) {
										m_shouldClose = true;
										m_show = false;

										OutlineLayer::OpenProject(path.path().stem().string());

										OutlineLayer::AttachEditor();
									}


									ImGui::PopStyleColor(3);
									ImGui::PopID();
								}
								ImGui::EndGroup();
							}

						}

						ImGui::EndListBox();
					}


					ImGui::EndChild();
				}


			ImGui::EndChild();
		}

		ImGui::PopStyleColor(clrCount);
		ImGui::PopStyleVar(varCount);


	}
	bool SetupWindow::Modal()
	{
		bool open = true;
		ImVec2 size = ImGui::GetWindowSize();
		ImVec2 lastPos = ImGui::GetWindowPos();

		ImGui::SetNextWindowSize({ 900, 600 });
		float halfWidth = size.x / 2;
		float halfHeight = size.y / 2;

		ImVec2 newPos = { lastPos.x + halfWidth - 450, lastPos.y + halfHeight - 300 };
		ImGui::SetNextWindowPos(newPos);

		if (ImGui::BeginPopupModal("New Project", &open, ImGuiWindowFlags_NoResize)) {
			auto c_pos = ImGui::GetCursorPos();
			ImGui::SetCursorPos({ c_pos.x + 15, c_pos.y + 15 });
			ImGui::Image(0, { 300, 300 });
			ImGui::SameLine();

			//ImGui::BeginGroup();
			{
				auto group_size = ImGui::GetContentRegionAvail();
				ImGui::PushItemWidth(group_size.x * 0.8f);

				ImGui::InputTextWithHint("###THIS ONE", "Project Name", &prj_name);
				ImGui::InputTextWithHint("###Projects/", "Project Directory", &prj_dir);

				ImGui::Text("%s", prj_dir.c_str());

				const char* apis[]{ "OpenGL", "DirectX", "Vulkan" };
				const char* pipelines[]{
					"High-Definition Render Pipeline (HDRP)",
					"3D",
					"2D"
				};

				ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0x7C, 0x4E, 0xFF, 0xFF));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(0x7C, 0x4E, 0xFF, 0xFF));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(0x7C, 0x4E, 0xFF, 0xFF));
				ImGui::Combo("###Graphics API", &selected_api, apis, IM_ARRAYSIZE(apis));
				ImGui::Combo("###Graphics Pipeline", &selected_pipeline, pipelines, IM_ARRAYSIZE(pipelines));
				ImGui::PopStyleColor(3);

			}
			//ImGui::EndGroup();

			ImGui::SetCursorPos({ ImGui::GetContentRegionAvailWidth() - 250, ImGui::GetCursorPosY() + 180 });
			if (ImGui::Button("Cancel")) {
				prj_name = "";
				prj_dir = "";
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();

			ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0x7C, 0x4E, 0xFF, 0xFF));
			
			
			
			if (ImGui::Button("Create")) {
				if (!prj_name.empty()) {
					m_shouldClose = true;
					m_show = false;


					OutlineLayer::CreateOutlineDirectory(prj_name);
					OutlineLayer::NewScene(prj_name);
					OutlineLayer::SaveScene();

					OutlineLayer::AttachEditor();

					ImGui::CloseCurrentPopup();
				}
				else {
					// error detection..
				}
			}
			
			
			
			ImGui::PopStyleColor();
			ImGui::EndPopup();
		}


		return true;
	}
}
