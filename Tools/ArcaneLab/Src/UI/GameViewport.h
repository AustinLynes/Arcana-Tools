#pragma once

#include <Engine/UI/DWindow.h>

namespace ArcanaTools {
	namespace UI {

		class GameViewport : public UIWindow
		{
		public:
			GameViewport();

			virtual void OnAttach() override;
			virtual void OnDetach() override;
			virtual void OnUpdate() override;
			virtual void OnRender() override;

		};

	}
}
