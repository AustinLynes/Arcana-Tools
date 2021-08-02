#pragma once

#include <entt/entt.hpp>

#include <Engine/Time/TimeStep.h>
#include <Engine/Graphics/assets/Skybox.h>
#include <Engine/Graphics/cameras/Camera.h>

#include <optional>


namespace ArcanaTools {

	class Entity;

	class Scene
	{
	public:
		Scene(const std::string& name="default");
		~Scene();
		void Initilize();

		Entity* CreateEntity(const std::string& name = "");
		Entity* CreateChildEntity(const std::string& name ="");


		std::vector<Entity*> GetAllEntities();
		Entity* GetSelectedEntity();
		void SetSelectedEntity(int id);

		void DrawToFramebuffer(Entity* camera);
		void OnUpdate(TimeStep ts);

		void OnResize(float width, float height);
		
		void OnRuntimeStart();
		void OnUpdateRuntime(TimeStep ts);
		void OnRuntimeExit();
		
		void DeleteEntity();

		const uint32_t& GetEntityCount() { return m_count; }
		
		Skybox* GetSkybox();

		bool ShouldPlay() { return m_play; }
	
		const std::string& GetName()  const { return m_name;  }
		const std::string& GetNameNoExtension() const { return m_name.substr(0, m_name.find_first_of('.')); }
		
		//template<typename T>
		//T* CreateBehavior() {
		//	return new T();
		//}

		//template<typename T>
		//void BindBehavior(Entity* entity) {
		//	entity->AddComponent<Components::NativeBehavior>().Bind<T>();
		//}

		static Scene* Create(const std::string& sceneName);

	private:
		std::string m_name;
		bool m_play = false;

		Skybox* m_skybox;
		uint32_t m_count = 0;

		entt::registry m_registry;

		friend class Entity;
		std::vector<Entity*> entities{};
		Entity* selected = nullptr;
		

	};


}

