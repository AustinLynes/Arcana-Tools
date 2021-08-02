#pragma once
#include <Engine/layers/Layer.h>

#include <string>
#include <unordered_map>
#include <Engine/Scene/Scene.h>
#include "UI/SetupWindow.h"
#include "UI/Dockspace.h"


namespace ArcanaTools {

	static bool s_allowRuntime = false;

	class OutlineLayer : public Layer
	{
	public:
		OutlineLayer() : Layer("OUTLINE_MANAGER") {}
		
		const char* s_BaseFilepath = "Outlines/";
		
		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnRender() override;
		virtual void OnUpdate(TimeStep ts) override;

		virtual void OnImGuiRender() override;

		static bool ShouldAllowRealtimeFunctions() { return s_allowRuntime; };
		
		static void AttachEditor();

		static void NewScene(const std::string& name);
		static void OpenScene(const std::string& name);

		static void OpenProject(const std::string& name);

		static void SaveScene();
		static void SaveSceneAs();
		
		static void CreateOutlineDirectory(const std::string& outlineName);
		static std::string GetOutlineFilePath();
		static OutlineLayer* Create(const std::string& targetDirectory);
	
	
		static Scene* GetActiveScene() { return m_activeScene; }

	private:


		static Scene* m_activeScene ;
		static std::string m_filepath;
		static std::string m_name;

		static bool has_completed_setup ;
		static bool should_attach_editor ;
		//SceneSerializer Serializer;

		Dockspace* m_dockspace ;
		SetupWindow* m_setupwindow ;

		
	};
}
