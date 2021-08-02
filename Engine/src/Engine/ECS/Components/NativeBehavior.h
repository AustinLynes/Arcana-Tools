#pragma once

#include "../Entity/Behavior.h"

namespace ArcanaTools {
	namespace Components {

		struct NativeBehavior {
			Behavior* Instance = nullptr;

			// function pointer lambda through std::function
			Behavior*(*InstantiateScript)();
			void(*DestroyScript)(NativeBehavior*);


			template<typename T>
			void Bind() {
				InstantiateScript = []() { return static_cast<Behavior*>(new T()); };
				DestroyScript	  = [](NativeBehavior* b) { delete b->Instance; b->Instance = nullptr; };
			}
		};
	}

}


/*
	entity.AddComponent<NATIVE_BEHAVIOR>().Bind<WHICH_COMPONENT_TO_BE_BOUND>()


*/