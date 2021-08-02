#include "AssetBrowserPanel.h"

#include "../OutlineLayer.h"

namespace ArcanaTools {

	void AssetBrowserPanel::OnAttach()
	{
		//m_path = s_AssetPath;

		icons["back_arrow"] = reinterpret_cast<ImTextureID>(Texture2D::Create("resources/icons/back_arrow.png", false)->GetTextureID());
		icons["forward_arrow"] = reinterpret_cast<ImTextureID>(Texture2D::Create("resources/icons/forward_arrow.png", false)->GetTextureID());
		icons["up_arrow"] = reinterpret_cast<ImTextureID>(Texture2D::Create("resources/icons/up_arrow.png", false)->GetTextureID());
		icons["import"] = reinterpret_cast<ImTextureID>(Texture2D::Create("resources/icons/import.png", false)->GetTextureID());
		icons["folder"] = reinterpret_cast<ImTextureID>(Texture2D::Create("resources/icons/folder.png", false)->GetTextureID());

		m_flags = ImGuiWindowFlags_NoCollapse;
		m_search = "";


		m_path = OutlineLayer::GetOutlineFilePath();
	}

	void AssetBrowserPanel::OnDetach()
	{
	}

	void AssetBrowserPanel::OnUpdate()
	{

	}

	void AssetBrowserPanel::MenuBar() {

		// BACK ARROW
		if (ImGui::ImageButton(icons["back_arrow"], { 16.0f, 16.0f })) {
			if (m_path.has_parent_path() && m_path.relative_path().string() != OutlineLayer::GetOutlineFilePath()) {
				m_forwardPath = m_path;
				m_path = m_path.parent_path();
			}
		}
		ImGui::SameLine();
		if (ImGui::ImageButton(icons["forward_arrow"], { 16.0f, 16.0f })) {
			if (m_forwardPath.relative_path() != "")
				m_path = m_forwardPath;

			m_forwardPath.relative_path() = "";

		}
		
	}


	void AssetBrowserPanel::ContentBrowserLeft(ImVec2 size)
	{
		int clrCount = 0;
		ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0x21, 0x21, 0x21, 0xFF)); clrCount++;
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 10.0f, 10.0f });
		
		std::string filterBuffer;

		if (ImGui::BeginChild("###AssetsLeft", size, true, ImGuiWindowFlags_AlwaysUseWindowPadding)) {

			
			if (ImGui::InputTextWithHint("", "Assets", &filterBuffer)) {

			}


			ImVec2 childSize = ImGui::GetContentRegionAvail();

			if (ImGui::BeginListBox("###ALLB", childSize)) {


				for (auto& path : std::filesystem::directory_iterator(m_path))
				{
					/*const char* _path_ = reinterpret_cast<const char*>(path.path().c_str());*/

					std::string _path_ = path.path().string();
					std::string filename = path.path().filename().stem().string();
					std::string extension = path.path().extension().string();

					if (path.is_directory()) {
						ImGui::Image(icons["folder"], { 16, 16 });
						ImGui::SameLine();
						ImGui::Text("%s", filename.c_str());
					}
					// determine extension
					else if (path.path().extension() == ".png" || path.path().extension() == ".jpg") {
						// LOAD THE TEXTURE... WRTIE THE TEXTURE
						ImGui::Text("%s", filename.c_str());
					}

				}

				ImGui::EndListBox();
			}
			ImGui::EndChild();
		}

		ImGui::PopStyleColor(clrCount);
		ImGui::PopStyleVar();
	}

	void AssetBrowserPanel::ContentBrowserRight(ImVec2 size)
	{
		int clrCount = 0;
		int varCount = 0;
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0,0 }); varCount++;
		ImGui::BeginGroup();
		ImGui::BeginChild("###ARCB", size, true);
		//------------------------------------------------------------------------------------------------------- 

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 5.0f, 0.0f });
		ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 4);

		ImGui::PushStyleColor(ImGuiCol_ChildBg, { 0,0,0,1 });
		ImGui::PushStyleColor(ImGuiCol_Border, { 0.10,0.10,0.10,1 });
		auto ns = ImGui::GetContentRegionAvail();

		if (ImGui::BeginChild("###ARSC", { ns.x, 24}, true, ImGuiWindowFlags_AlwaysUseWindowPadding)) {

			ImVec2 lastPos = ImGui::GetCursorPos();
			ImGui::SetCursorPos({ lastPos.x, lastPos.y + 3 });
			ImGui::Image(icons["folder"], { 16.0f, 16.0f });
			ImGui::SameLine();
			lastPos = ImGui::GetCursorPos();
			ImGui::SetCursorPos({ lastPos.x + 5, lastPos.y + 2 });
			curPath =  m_path.relative_path().string().substr(
				m_path.relative_path().string().find_first_of('/')+1,
				m_path.relative_path().string().size()
			);

			ImGui::TextColored({ 1,1,1,1 }, "%s", curPath.c_str());
		
			ImGui::EndChild();
		}
		
		ImGui::PopStyleVar(2);
		ImGui::PopStyleColor(2);

		//-------------------------------------------------------------------------------------------------- BROWSING SECTION
		ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0x13, 0x13, 0x13, 0xFF)); clrCount++;
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0); varCount++;
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0); varCount++;
		auto childSize = ImGui::GetContentRegionAvail();
		if (ImGui::BeginListBox("###AssetsRight", childSize)) {

			for (auto& path : std::filesystem::directory_iterator(m_path))
			{


				/*const char* _path_ = reinterpret_cast<const char*>(path.path().c_str());*/
				ImGui::BeginGroup();
				ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0,0 });

				std::string _path_ = path.path().string();
				std::string filename = path.path().filename().stem().string();
				std::string extension = path.path().extension().string();

				if (path.is_directory()) {
					ImGui::ImageButton(icons["folder"], { 96, 96 });
					if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
						directory_loaded_textures = false;
						m_path /= path.path().filename();
						ImGui::EndGroup();
						ImGui::PopStyleVar();
						didBreak = true;
						break;
					}
					ImVec2 lastPos = ImGui::GetCursorPos();
					ImGui::SetCursorPos({ lastPos.x + 96.0f, lastPos.y - 20.0f});
					ImGui::Text("%s", filename.c_str());
				}
				// determine extension
				else if (path.path().extension() == ".png" || path.path().extension() == ".jpg") {
					// LOAD THE TEXTURE... WRTIE THE TEXTURE
					if (!directory_loaded_textures) {
						loaded_textures[filename] = Texture2D::Create(_path_, false);
					}
					ImGui::ImageButton((ImTextureID)loaded_textures[filename]->GetTextureID(), { 96, 96 });
					ImVec2 lastPos = ImGui::GetCursorPos();
					ImGui::SetCursorPos({ lastPos.x + 20, lastPos.y});
					ImGui::Text("%s", filename.c_str());

					
				}
				
				ImGui::EndGroup();
				//ImGui::NextColumn();
				ImGui::PopStyleVar();
				ImGui::SameLine();
			}

			if (!didBreak) {
				directory_loaded_textures = true;
			}
			else {
				didBreak = false;
			}

			ImGui::EndListBox();

		}
		ImGui::PopStyleColor(clrCount);
		ImGui::PopStyleVar(varCount);
		ImGui::EndChild();

		ImGui::EndGroup();
	}

	void AssetBrowserPanel::OnRender()
	{

		int varCount = 0;
		int clrCount = 0;
		if (m_show) {

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0,0 }); varCount++;
			 

			if (!Begin(m_tag.c_str())) {
				ImGui::PopStyleVar(varCount);

				return;
			}
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 }); varCount++;

			MenuBar();
			//static float columnWidth = 300.0f;
			//ImGui::Columns(2, "###Content_Panels");
			//ImGui::SetColumnWidth(0, columnWidth);

			// LEFT COLUMN
			ImVec2 left_size = { ImGui::GetContentRegionAvail().x * 0.2f,  ImGui::GetContentRegionAvail().y };
			ContentBrowserLeft(left_size);
			//ImGui::NextColumn();
			ImGui::SameLine();
			// RIGHT COLUMN

			ImVec2 right_size = ImGui::GetContentRegionAvail();
			ContentBrowserRight(right_size);

			ImGui::PopStyleVar(varCount);
			ImGui::PopStyleColor(clrCount);
			
			End();


		}

	}
}