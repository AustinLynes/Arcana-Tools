#include"Camera.h"

#include <engine/Window/Window.h>
#include "..\..\ECS\Components\Camera.h"

namespace ArcanaTools {

	
	Camera::Camera(float width, float height, float fieldOfView, float nearZ, float farZ, bool is_editor) : 
		m_projection(glm::perspective(glm::radians(fieldOfView), width / height, nearZ, farZ)), 
		width(width), 
		height(width), 
		FOV(fieldOfView), 
		nearZ(nearZ), 
		farZ(farZ)
	{
	
	}

	void Camera::SetAspectRatio(float _width, float _height)
	{
		width = _width;
		height = _height;
		m_projection = glm::mat4(1.0f);
		m_projection = glm::perspective(glm::radians(FOV), width / height, nearZ, farZ);
	}

	float Camera::GetFieldOfView()
	{
		return FOV;
	}

	void Camera::SetFieldOfView(float fieldOfView)
	{
		FOV = fieldOfView;
	}

	float Camera::GetNearClipPlane()
	{
		return nearZ;
	}

	void Camera::SetNearClipPlane(float _nearZ)
	{
		nearZ = _nearZ;
	}

	float Camera::GetFarClipPlane()
	{
		return farZ;
	}

	void Camera::SetFarClipPlane(float _farZ)
	{
		farZ = _farZ;
	}

}
