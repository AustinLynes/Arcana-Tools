#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace ArcanaTools {

	class Camera
	{
	public:
		Camera(float width = 800, float height = 600, float fieldOfView = 45.0f, float nearZ = 0.1f, float farZ = 100.0f, bool is_editor = false);
		Camera(const Camera& _copy) = default;
		Camera& operator=(Camera& _assign) = default;

		void SetAspectRatio(float _width, float _height);
		glm::vec2 GetAspectRatio() { return { width, height }; };

		float GetFieldOfView();
		void SetFieldOfView(float fieldOfView);

		float GetNearClipPlane();
		void SetNearClipPlane(float nearZ);

		float GetFarClipPlane();
		void SetFarClipPlane(float farZ);
		
		float GetWidth() { return width; }
		float GetHeight() { return width; }

		glm::mat4  GetProjectionMatrix() { m_projection = glm::perspective(glm::radians(FOV), width / height, nearZ, farZ); return m_projection; }
		
		
		void SetEditorCamera(bool value) { m_isEditorCamera = value; }
		bool IsEditorCamera() { return m_isEditorCamera; }

		void SetPrimaryCamera(bool value) { m_isPrimaryCamera = value; }
		bool IsPrimaryCamera() { return m_isPrimaryCamera; }


	private:

		float width;
		float height;
		float FOV;
		float nearZ;
		float farZ;
		
		bool m_isEditorCamera = false;
		bool m_isPrimaryCamera = false;
		
		glm::mat4 m_projection = glm::mat4(1.0f);
		
	};

}
