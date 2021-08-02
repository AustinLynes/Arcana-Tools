#include "DWindow.h"

namespace ArcanaTools {
	namespace UI {
		void UIWindow::OnRender()
		{
			{
				if (m_show) {
					if (!Begin(m_tag.c_str()))
						return;

					// DISPLAY ALL CHILDREN

					End();
				}

			};
		}
		const std::string& UIWindow::GetTag()
		{
			return m_tag;
		}
		bool UIWindow::Begin(const char* title)
		{
			m_class = ImGuiWindowClass();
			m_class.DockNodeFlagsOverrideSet = m_dnflags;

			ImGui::SetNextWindowClass(&m_class);
			if (!ImGui::Begin(title, &m_show, m_flags)) {
				ImGui::End();
				return false;
			}

			return true;
		}
		void UIWindow::End()
		{
			ImGui::End();
		}

		
	}
}