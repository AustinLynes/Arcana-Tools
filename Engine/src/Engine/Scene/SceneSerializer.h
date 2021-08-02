#pragma once

#include <Engine/Scene/Scene.h>


namespace ArcanaTools {

	class SceneSerializer {
	public:
		SceneSerializer(Scene* scene);
		void Serialize(const std::string& filepath);
		bool Deserialize(const std::string& filepath);
		Scene* GetScene() { return m_Scene; }
	
	private:
		Scene* m_Scene = nullptr;
	};

}