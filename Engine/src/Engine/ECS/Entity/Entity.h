#pragma once

#include "entt/entt.hpp"
#include "Engine/Scene/Scene.h"

namespace ArcanaTools {

	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene, bool child) :  m_handle(handle), m_scene(scene), is_child(child) {}
		Entity(const Entity& _other) = default;
		Entity& operator=(const Entity& _other) = default;
		~Entity() {}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args) {
			if (HasComponent<T>())
				return m_scene->m_registry.replace<T>(m_handle, std::forward<Args>(args)...);
			else
				return m_scene->m_registry.emplace<T>(m_handle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent() {
			//assert(!HasComponent<T>() && "DOES NOT HAVE COMPONENT");
			return m_scene->m_registry.get<T>(m_handle);

		}
		template<typename T>
		bool HasComponent() {
			return m_scene->m_registry.all_of<T>(m_handle);
		}

		template<typename T>
		void RemoveComponent() {
			m_scene->m_registry.remove<T>(m_handle);
		}

		int GetID() { return (int)m_handle; }
		bool operator==(const Entity& other) const
		{
			return m_handle == other.m_handle && m_scene == other.m_scene;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}

		void AddChild(Entity* child) {
			children[children_count++] = child;
		}
		bool IsChild() { return is_child; }
		std::unordered_map<uint32_t, Entity*> GetChildren() {
			return children;
		}

	private:
		entt::entity m_handle;
		Scene* m_scene;


		std::unordered_map<uint32_t, Entity*> children;
		uint32_t children_count = 0;
		bool is_child = false;
	};


	
}

