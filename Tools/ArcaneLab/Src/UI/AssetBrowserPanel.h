#pragma once

#include <iostream>
#include <filesystem>
#include <Engine/UI/DWindow.h>
#include "Engine/Graphics/assets/Texture.h"
#include <unordered_map>

#include <imgui/imgui_internal.h>
namespace ArcanaTools {
	using namespace UI;
	
	class AssetBrowserPanel : public UIWindow
	{
	public:
		AssetBrowserPanel() : UIWindow("Assets") {}

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnRender() override;

		void MenuBar();
		void ContentBrowserLeft(ImVec2 size);
		void ContentBrowserRight(ImVec2 size);

	private:
		std::string m_filepath;

		std::string m_search;
		std::string curPath;

		std::filesystem::path m_path;
		std::filesystem::path m_forwardPath;
		Texture2D* folder_icon;
		Texture2D* import_icon;

		std::unordered_map<std::string, Texture2D*> loaded_textures;
		std::unordered_map<std::string, ImTextureID> icons;
		bool directory_loaded_textures = false;
		bool didBreak = false;
	};

}
