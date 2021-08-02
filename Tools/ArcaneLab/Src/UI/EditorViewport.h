#pragma once

#include <Engine/UI/DWindow.h>
#include <glm/glm.hpp>

namespace ArcanaTools {
	namespace UI {

		enum class TransformMode {
			Translate,
			Rotate,
			Scale
		};

		class EditorViewport : public UIWindow
		{
		public:
			EditorViewport();

			virtual void OnAttach() override;
			virtual void OnDetach() override;
			virtual void OnUpdate() override;
			virtual void OnRender() override;

		private:

			static TransformMode mode;
			int entity_hovered = -1;
			bool is_usingGizmo = false;
			bool is_gizmoHovered = false;
		
			bool m_ViewportFocused = false, m_ViewportHovered = false;
			glm::vec2 m_ViewportBounds[2]{ {0.0f,0.0f} ,{0.0f,0.0f} };
			glm::vec2 m_ViewportSize = { 0.0f,0.0f };
		};

	}
}

