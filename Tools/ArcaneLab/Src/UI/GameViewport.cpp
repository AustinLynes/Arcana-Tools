#include "GameViewport.h"


#include "../GameLayer.h"
#include <Engine/Graphics/renderers/Renderer3D.h>
#include "../OutlineLayer.h"

namespace ArcanaTools {
	namespace UI {

		GameViewport::GameViewport() : UIWindow("Game") {}

		void GameViewport::OnAttach()
		{
			
		}
		void GameViewport::OnDetach()
		{
		}
		void GameViewport::OnUpdate()
		{
			
		}
		void GameViewport::OnRender()
		{
			m_flags = ImGuiWindowFlags_NoCollapse;

			if (m_show) {

				

				if (!Begin(GetTag().c_str())) {
					return;
				}

				ImGui::BeginChild("###GAME");
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0,0 });
				ImVec2 winSize = ImGui::GetContentRegionAvail();


				ImVec2 winPos = ImGui::GetWindowPos();
				
				auto entities = OutlineLayer::GetActiveScene()->GetAllEntities();
				for (auto ent : entities)
				{
					if (ent->HasComponent<Components::PerspectiveCamera>()) {
						auto camComp = ent->GetComponent<Components::PerspectiveCamera>();
						if (camComp.GetInstance()->IsPrimaryCamera()) {

							camComp.GetInstance()->SetAspectRatio(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y);
						}
					}
				}

				ImGui::Image((void*)GameLayer::GetFrameBuffer()->GetColorAttachmentRendererID(), winSize, { 0,1 }, { 1,0 });

				ImGui::PopStyleVar(1);
				ImGui::EndChild();

				End();
			}

		}
	}
}
