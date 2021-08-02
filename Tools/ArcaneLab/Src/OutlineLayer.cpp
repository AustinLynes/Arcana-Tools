#include "OutlineLayer.h"

#include "Engine/Utils/PlatformUtils.h"
#include <Engine/Scene/SceneSerializer.cpp>
#include "Engine/layers/LayerStack.h"
#include "EditorLayer.h"
#include "GameLayer.h"

namespace ArcanaTools {
	std::string OutlineLayer::m_name = "";
	std::string OutlineLayer::m_filepath="";


	bool OutlineLayer::has_completed_setup = false;
	bool OutlineLayer::should_attach_editor = false;
	//SceneSerializer Serializer;
	Scene* OutlineLayer::m_activeScene = nullptr;

	void OutlineLayer::SaveScene()
	{
		if (!m_filepath.empty()) {
			std::string out = m_filepath + m_name;

			SceneSerializer ser(m_activeScene);
			ser.Serialize(out);
		}
	}

	void OutlineLayer::SaveSceneAs()
	{
		std::optional<std::string> filepath = Utils::FileDialog::SaveFile("Arcana Tools Scene File (*.scene)\0*.scene\0");
		if (filepath) {
			m_filepath = filepath.value();
			SceneSerializer ser(m_activeScene);
			ser.Serialize(*filepath);
		}
	}

	void OutlineLayer::OpenScene(const std::string& name)
	{
		std::optional<std::string> filepath = Utils::FileDialog::OpenFile("Arcana Tools Scene File (*.scene)\0*.scene\0");
		if (filepath) {
			m_name = name;

			NewScene(name);
			//delete m_activeScene;
			SceneSerializer ser(m_activeScene);
			ser.Deserialize(*filepath);
			m_activeScene->Initilize();
		}
	}

	void OutlineLayer::OpenProject(const std::string& name)
	{
		m_name = name;
		//delete m_activeScene;
		NewScene(name);
		SceneSerializer ser(m_activeScene);
		ser.Deserialize("Outlines/" + name + "/" + name + ".scene");
		m_activeScene->Initilize();
	}



	void OutlineLayer::OnAttach()
	{
		m_dockspace = new Dockspace();
		m_setupwindow = new SetupWindow();

		m_dockspace->OnAttach();
		m_setupwindow->OnAttach();
		
	}

	void OutlineLayer::OnDetach()
	{
		// PROBABLY DELETE THE DYNAMIC MEMOR
		delete m_activeScene;

	}

	
	void OutlineLayer::OnRender()
	{
		// NOT SURE WHY I OVERIDED THIS
	}

	void OutlineLayer::OnUpdate(TimeStep ts)
	{
	}

	void OutlineLayer::OnImGuiRender()
	{
		static bool show = true;
		m_dockspace->OnRender();
		m_setupwindow->OnRender();
	}

	void OutlineLayer::AttachEditor()
	{
		LayerStack::AttachLayers({ new EditorLayer() , new GameLayer() });
		should_attach_editor = false;
		s_allowRuntime = true;
	}

	void OutlineLayer::NewScene(const std::string& name)
	{
		delete m_activeScene;
		m_name = name;
		// there should eventually be an opton to create an empty scene 
		m_activeScene = Scene::Create(name);// <<--- like this or.. create one with some default props
		//SceneSerializer ser(m_activeScene);
		/*ser.Serialize("Outlines/" + name + "/" + name + ".scene");
		m_activeScene->Initilize();*/
	}

	/*
	Arcana
	  |
	  + --- Outlines
			  |
			  + --- Project Name
							|
							+ --- Assets
									|
									+ --- Models
									|
									+ --- Textures
									|
									+ --- Scripts

	*/
	void OutlineLayer::CreateOutlineDirectory(const std::string& outline_name) {
		m_name = outline_name + "/";
		
		
		std::string out		  = m_filepath + m_name;
		std::string _models   = m_filepath + m_name + "Models";
		std::string _textures = m_filepath + m_name + "Textures";
		std::string _scripts  = m_filepath + m_name + "Scripts";
		
		std::filesystem::create_directory(out);
		std::filesystem::create_directory(_models);
		std::filesystem::create_directory(_textures);
		std::filesystem::create_directory(_scripts);


	}

	std::string OutlineLayer::GetOutlineFilePath()
	{
		return m_filepath + m_name;
	}

	OutlineLayer* OutlineLayer::Create(const std::string& targetDirectory)
	{
		m_filepath = targetDirectory;
		std::filesystem::create_directory(targetDirectory);
		return new OutlineLayer();
	}

	
}
