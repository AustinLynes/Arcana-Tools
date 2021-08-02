#pragma once
#include <iostream>
namespace ArcanaTools {
	namespace Components {
		struct CameraController {

			CameraController() {}
			~CameraController() {}
			CameraController(const CameraController& other) = default;

		
			glm::mat4 GetViewMatrix(glm::vec3 _position) {
				UpdateViewMatrix(_position);
				/*std::cout << "Yaw: " << m_Yaw << std::endl 
					<< "Pitch: " << m_Pitch << std::endl;*/
				return m_ViewMatrix;
			}
			
			glm::vec3 Up() {
				return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
			}
			glm::vec3 Right() {
				return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
			}
			glm::vec3 Forward(){
				return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));

			}
			
			float GetPitch() {  return m_Pitch;  }
			float GetYaw() { return m_Yaw; }

			void SetYaw(float nYaw) { m_Yaw = nYaw; }
			void SetPitch(float nPitch, bool constrain = true) { m_Pitch = nPitch; }

			float GetRotationSpeed() { return m_RotationSpeed; }
			void SetRotationSpeed(float speed) { m_RotationSpeed = speed; }
		
		private:	
			
			const glm::quat& GetOrientation() {
				m_orientation = glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
				return m_orientation;
			}

			void UpdateViewMatrix(glm::vec3 _position)
			{
				m_orientation = GetOrientation();
				m_ViewMatrix = glm::translate(glm::mat4(1.0f), _position) * glm::toMat4(m_orientation);
				m_ViewMatrix = glm::inverse(m_ViewMatrix);
			}


		private:

			float m_Pitch = 0.0f;
			float m_Yaw = 0.0f;
			float m_RotationSpeed = 1.00f;

			glm::quat m_orientation = glm::quat(0,0,0,0);

			glm::mat4 m_ViewMatrix = glm::mat4(1.0f);

		};

	}
}