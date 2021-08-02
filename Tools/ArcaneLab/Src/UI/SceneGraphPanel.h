#pragma once

#include <Engine/UI/DWindow.h>

namespace ArcanaTools {
	namespace UI {
		class SceneGraphPanel : public UIWindow
		{
		public:
			SceneGraphPanel();

			virtual void OnAttach() override;
			virtual void OnDetach() override;
			virtual void OnUpdate() override;
			virtual void OnRender() override;
		};

	}
}

