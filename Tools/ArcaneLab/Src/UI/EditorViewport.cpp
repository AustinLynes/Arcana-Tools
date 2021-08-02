#include "EditorViewport.h"


// ACCESS TO FRAMEBUFFERS
#include "../EditorLayer.h"

// Input
#include "Engine/Input/Input.h"

#include "../OutlineLayer.h"

namespace ArcanaTools {
	namespace UI {
		TransformMode EditorViewport::mode = TransformMode::Scale;

		EditorViewport::EditorViewport() : UIWindow("Editor Viewport") {}

		void EditorViewport::OnAttach()
		{

		}
		void EditorViewport::OnDetach()
		{
		}
		void EditorViewport::OnUpdate()
		{

			if (Input::IsKeyPressed(Key::W)) {
				mode = UI::TransformMode::Translate;
			}
			if (Input::IsKeyPressed(Key::R)) {
				mode = UI::TransformMode::Rotate;
			}
			if (Input::IsKeyPressed(Key::S)) {
				mode = UI::TransformMode::Scale;
			}

			if (FrameBufferSpecification spec = EditorLayer::GetFrameBuffer()->GetSpecification();
				m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
				(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
			{
				EditorLayer::GetFrameBuffer()->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
				EditorLayer::GetCamera()->GetComponent<Components::PerspectiveCamera>().GetInstance()->SetAspectRatio(m_ViewportSize.x, m_ViewportSize.y);
				//m_EditorCamera.SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
				OutlineLayer::GetActiveScene()->OnResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			}

		}
		void DrawGrid(const glm::mat4 viewMatrix, const glm::mat4& projectiomMatrix, const glm::vec3& basis, float size) {
			glm::mat4 current_grid = glm::mat4(1.0f);
			current_grid *= glm::rotate(viewMatrix, glm::radians(90.0f), basis);
			float grid_color[4]{ 1.0f, 1.0f, 1.0f, 1.0f };

			ImGuizmo::DrawGrid(
				glm::value_ptr(viewMatrix),
				glm::value_ptr(projectiomMatrix),
				value_ptr(glm::mat4(1.0f)),
				size
			);

		}


		void EditorViewport::OnRender()
		{
			static bool isLocal;
			ImVec2 winSize = ImGui::GetContentRegionMax();

			if (m_show) {

				m_flags = /*ImGuiWindowFlags_NoMove |*/ ImGuiWindowFlags_NoCollapse;

				if (!Begin(GetTag().c_str())) {
					return;
				}

				ImGuizmo::BeginFrame();

				ImGui::BeginChild("###Renderer");
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0,0 });

				auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
				auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
				auto viewportOffset = ImGui::GetWindowPos();
				m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
				m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };
				
				
				EditorLayer::GetFrameBuffer()->Bind();
				//EditorLayer::GetFrameBuffer()->ClearAttachment(1, -1);
				auto [mx, my] = ImGui::GetMousePos();
				mx -= m_ViewportBounds[0].x;
				my -= m_ViewportBounds[0].y;
				m_ViewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];
				my = m_ViewportSize.y - my;
				int mouseX = (int)mx;
				int mouseY = (int)my;
				if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)m_ViewportSize.x && mouseY < (int)m_ViewportSize.y)
				{
					if (!is_gizmoHovered) {
						int pData = EditorLayer::GetFrameBuffer()->ReadPixel(1, mouseX, mouseY);
						//std::cout << pData << std::endl;
						int selected = pData == -1 ? -1 : pData;
						entity_hovered = selected;
						if (Input::IsMouseButtonPressed(Mouse::Button0) && entity_hovered > -1 && !is_usingGizmo) {
							OutlineLayer::GetActiveScene()->SetSelectedEntity(entity_hovered);
						}
					}
				}
				EditorLayer::GetFrameBuffer()->Unbind();
				// POST PROCESSING
				//unsigned int amount = 10;
				//bool horz = true;
				//EditorLayer::GetFrameBuffer()->Bind();
				//glBindTexture(GL_TEXTURE_2D, EditorLayer::GetFrameBuffer()->GetColorAttachmentRendererID(0));
				//for (unsigned int i = 0; i < amount; i++)
				//{
				//	EditorLayer::GetFrameBuffer()->GetColorAttachmentRendererID(2);
				//	glBindTexture(GL_TEXTURE_2D, EditorLayer::GetFrameBuffer()->GetColorAttachmentRendererID(horz ? 0 : 2));
				//	horz = !horz;
				//}
				//glBindTexture(GL_TEXTURE0, EditorLayer::GetFrameBuffer()->GetColorAttachmentRendererID(0));
				//glBindTexture(GL_TEXTURE1, EditorLayer::GetFrameBuffer()->GetColorAttachmentRendererID(2));
				//EditorLayer::GetFrameBuffer()->Unbind();


				ImGui::Image((void*)EditorLayer::GetFrameBuffer()->GetColorAttachmentRendererID(0), { m_ViewportSize.x, m_ViewportSize.y }, { 0,1 }, { 1,0 });

				auto entities = OutlineLayer::GetActiveScene()->GetAllEntities();
				ImGuizmo::SetOrthographic(false);
				float winWidth = (float)ImGui::GetWindowWidth();
				float winHeight = (float)ImGui::GetWindowHeight();
				ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, winWidth, winHeight);
				ImGuizmo::SetDrawlist();

				glm::mat4 camView = EditorLayer::GetCamera()->GetComponent<Components::CameraController>().GetViewMatrix(EditorLayer::GetCamera()->GetComponent<Components::Transform>().GetPosition());
				//EditorLayer::GetCamera()->SetFarClipPlane(1000.0f);

				static bool showGrids = true;

				auto proj = EditorLayer::GetCamera()->GetComponent<Components::PerspectiveCamera>().GetInstance()->GetProjectionMatrix();

				if (showGrids) {
					DrawGrid(camView, proj, { 0, 1, 0 }, 50.0f);
				}


				auto selected = OutlineLayer::GetActiveScene()->GetSelectedEntity();
				if (selected) {

					auto entity = OutlineLayer::GetActiveScene()->GetSelectedEntity();
					glm::mat4 transform = entity->GetComponent<Components::Transform>().GetTransform();

					switch (mode) {
					case TransformMode::Translate: // translate 
						ImGuizmo::Manipulate(
							glm::value_ptr(camView),
							glm::value_ptr(proj),
							ImGuizmo::OPERATION::TRANSLATE, (ImGuizmo::MODE)isLocal, glm::value_ptr(transform)
						);
						break;
					case TransformMode::Rotate: // rotate 
						ImGuizmo::Manipulate(
							glm::value_ptr(camView),
							glm::value_ptr(proj),
							ImGuizmo::OPERATION::ROTATE, (ImGuizmo::MODE)isLocal, glm::value_ptr(transform)
						);
						break;
					case TransformMode::Scale: // scale
						ImGuizmo::Manipulate(
							glm::value_ptr(camView),
							glm::value_ptr(proj),
							ImGuizmo::OPERATION::SCALE, (ImGuizmo::MODE)isLocal, glm::value_ptr(transform)
						);
						break;

					}
					is_gizmoHovered = ImGuizmo::IsOver();

					if (ImGuizmo::IsUsing()) {

						glm::vec3 position, scale, rotation;
						ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(transform), glm::value_ptr(position), glm::value_ptr(rotation), glm::value_ptr(scale));

						switch (mode)
						{
						case TransformMode::Translate:
							entity->GetComponent<Components::Transform>().SetPosition(position);
							break;
						case TransformMode::Rotate:
						{
							glm::vec3 rot = entity->GetComponent<Components::Transform>().GetRotation();
							glm::vec3 drot = rotation - rot;
							rot.x += drot.x;
							rot.y += drot.y;
							rot.z += drot.z;
							if (entity->HasComponent<Components::CameraController>()) {
								auto& pc_comp = entity->GetComponent<Components::CameraController>();
								pc_comp.SetYaw(rot.y);
								pc_comp.SetPitch(rot.x);
							}
							entity->GetComponent<Components::Transform>().SetRotation(rot);
						}
							break;
						case TransformMode::Scale:
							entity->GetComponent<Components::Transform>().SetScale(scale);
							break;
						default:
							break;
						}
						is_usingGizmo = true;

					}
					else {
						is_usingGizmo = false;

					}

				}

				ImGui::PopStyleVar(1);
				ImGui::EndChild();

				End();
				
			}


		}
	}
}
