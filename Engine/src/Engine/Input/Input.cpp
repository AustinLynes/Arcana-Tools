#include "Input.h"
#include "Engine/Window/Window.h"

namespace ArcanaTools {
	bool Input::IsKeyPressed(const KeyCode key)
	{
		auto* window = static_cast<GLFWwindow*>(Window::GetGLFWWindow());
		auto state = glfwGetKey(window, static_cast<int32_t>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool ArcanaTools::Input::IsMouseButtonPressed(const MouseCode mouse)
	{
		auto* window = static_cast<GLFWwindow*>(Window::GetGLFWWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(mouse));
		return state == GLFW_PRESS;
	}
	glm::vec2 Input::GetMousePosition()
	{
		auto* window = static_cast<GLFWwindow*>(Window::GetGLFWWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return { (float)xPos,(float)yPos };
	}
	float Input::GetMouseY()
	{

		return GetMousePosition().y;
	}
	float Input::GetMouseX()
	{
		return GetMousePosition().x;
	}
}