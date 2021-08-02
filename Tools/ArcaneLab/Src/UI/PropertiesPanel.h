#pragma once

#include <Engine/UI/DWindow.h>

namespace ArcanaTools {
	namespace UI {
		class PropertiesPanel : public UIWindow
		{
		public:
			PropertiesPanel();
			virtual void OnAttach() override;
			virtual void OnDetach() override;
			virtual void OnUpdate() override;
			virtual void OnRender() override;

		};

	}
}

