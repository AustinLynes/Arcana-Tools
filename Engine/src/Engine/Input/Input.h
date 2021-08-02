#pragma once
#include "KeyCodes.h"
#include "glm/glm.hpp"
namespace ArcanaTools {
	class Input {
	public:
		static bool IsKeyPressed(const KeyCode key);
		static bool IsMouseButtonPressed(const MouseCode mouse);
		static glm::vec2 GetMousePosition();
		static float GetMouseY();
		static float GetMouseX();
	};
}