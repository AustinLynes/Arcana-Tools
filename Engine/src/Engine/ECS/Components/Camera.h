#pragma once
#include "Engine/Graphics/cameras/Camera.h"

namespace ArcanaTools{

	namespace Components {


		struct PerspectiveCamera {

			PerspectiveCamera() { m_Camera = new Camera(1920.0f, 1080.0f, 45.0f, 0.01f, 100.0f, false); }
			PerspectiveCamera(float width, float height, float fov, float nearZ, float farZ, bool isEditor) { m_Camera = new Camera(width, height, fov, nearZ, farZ, isEditor); }
			~PerspectiveCamera() {  }

			PerspectiveCamera(const PerspectiveCamera&) = default;

			Camera* GetInstance() { return m_Camera; };
			const Camera* GetInstance() const { return m_Camera; };

		private:
			Camera* m_Camera = nullptr;
		};

	}
}