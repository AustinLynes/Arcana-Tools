#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ArcanaTools {
	namespace Components {
		struct Transform {

			Transform() {};
			Transform(const Transform& other) = default;


			void SetPosition(const glm::vec3& newPos) {
				m_position = newPos;
			}

			void SetRotation(glm::vec3 _rotation) {
				m_rotation = _rotation;
			}

			void SetScale(const glm::vec3& _scale) {
				m_scale = _scale;

			}

			glm::vec3 GetPosition() { return m_position; }
			
			glm::vec3 GetRotation() { return m_rotation; }
			

			glm::vec3 GetScale() { 
				m_scaleMatrix = glm::scale(glm::mat4(1.0f), m_scale);

				return m_scale; 
			}

			glm::mat4 GetScaleMatrix() { return m_scaleMatrix; }
			glm::mat4 GetRotationMatrix() { 
				m_rotationMatrix = glm::toMat4(glm::quat({ glm::radians(m_rotation.x), glm::radians(m_rotation.y), glm::radians(m_rotation.z) }));

				return m_rotationMatrix; 
			}

			const glm::mat4& GetTransform() {

				//glm::mat4 rot =;
				//m_scale =;
				////;

				// [YES]  [T][R][S]


				m_transformMatrix = glm::translate(glm::mat4(1.0f), m_position);
				/*m_transformMatrix *= m_rotationMatrix;
				m_transformMatrix *= m_scaleMatrix;*/

				return m_transformMatrix;
					
					
			}

			void SetParentTransform(const glm::mat4& parentTrans) {
				m_parent = parentTrans;
			}
		private:
			glm::vec3 m_position = glm::vec3(0.0f);
			glm::vec3 m_rotation = glm::vec3(0.0f);
			glm::vec3 m_scale = glm::vec3(1.0f);

			glm::mat4 m_transformMatrix = glm::mat4(1.0f);
			glm::mat4 m_scaleMatrix = glm::scale(glm::mat4(1.0f), { 1.0,1.0,1.0 });
			glm::mat4 m_rotationMatrix = glm::scale(glm::mat4(1.0f), { 1.0,1.0,1.0 });
			
			glm::mat4 m_parent = glm::mat4(1.0f);
		};
	}
}