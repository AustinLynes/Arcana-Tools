#include "ConsoleWindow.h"

namespace ArcanaTools {
	namespace UI {
		ConsoleWindow::ConsoleWindow() : UIWindow("Console") {}
		
		void ConsoleWindow::OnAttach()
		{
		}

		void ConsoleWindow::OnDetach()
		{
		}
		void ConsoleWindow::OnUpdate()
		{
		}
		void ConsoleWindow::OnRender()
		{
			if (m_show) {
				
				 

				if (!Begin(GetTag().c_str())) {
					return;
				}



				End();
			}
		}
	}
}