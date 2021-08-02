#pragma once

#include "Entity.h"

// ALL SCRIPTS SHOULD INHERIT FROM THIS
namespace ArcanaTools {
	
	class Behavior {
	public:

		virtual void Start() = 0;
		virtual void Update(TimeStep ts) = 0;
		virtual void Destroy() {};

		template<typename T>
		T& GetComponent() {
			return m_entity.GetComponent<T>();
		}

		template<typename T>
		bool HasComponent() {
			return m_entity.HasComponent<T>();
		}

	private:
		Entity m_entity;
		friend Scene; // Scene can access private members of this class;
	};

}