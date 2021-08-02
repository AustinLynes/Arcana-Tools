#include "SceneGraphPanel.h"

#include "../EditorLayer.h"
#include "../OutlineLayer.h"

namespace ArcanaTools {
	namespace UI {
		SceneGraphPanel::SceneGraphPanel() : UIWindow("Scene Graph") { }

		void SceneGraphPanel::OnAttach()
		{
		}
		void SceneGraphPanel::OnDetach()
		{
		}
		void SceneGraphPanel::OnUpdate()
		{
		}
		void SceneGraphPanel::OnRender()
		{
			if (m_show) {


				if (!Begin(GetTag().c_str())) {
					return;
				}

				const ImVec2& winSize = ImGui::GetContentRegionAvail();

				if (ImGui::BeginListBox("###SCENE_GRAPH", winSize)) {


					const auto& entities = OutlineLayer::GetActiveScene()->GetAllEntities();

					ImGui::PushID("###EMPTY");
					if (ImGui::BeginPopupContextWindow("###EMPTY")) {
						if (ImGui::MenuItem("Empty Game Object")) {
							auto entity = OutlineLayer::GetActiveScene()->CreateEntity("Empty");
							OutlineLayer::GetActiveScene()->SetSelectedEntity(entity->GetID());
						}
						if (ImGui::BeginMenu("3D Object")) {
							if (ImGui::MenuItem("Cube")) {
								auto entity = OutlineLayer::GetActiveScene()->CreateEntity("Cube");
								
								auto& mr = entity->AddComponent<Components::MeshRenderer>();
								mr.LoadModel("Resources/Models/cube/cube.gltf");
								entity->AddComponent<Components::Material>();

								OutlineLayer::GetActiveScene()->SetSelectedEntity(entity->GetID());
							}

							if (ImGui::MenuItem("Plane")) {
								auto entity = OutlineLayer::GetActiveScene()->CreateEntity("Plane");


								auto& mr = entity->AddComponent<Components::MeshRenderer>();
								mr.LoadModel("Resources/Models/plane/scene.gltf");

								entity->AddComponent<Components::Material>();


								OutlineLayer::GetActiveScene()->SetSelectedEntity(entity->GetID());
							}

							if (ImGui::MenuItem("Sphere")) {
								auto entity = OutlineLayer::GetActiveScene()->CreateEntity("Sphere");

								auto& mr = entity->AddComponent<Components::MeshRenderer>();
								mr.LoadModel("Resources/Models/sphere/scene.gltf");

								
								entity->AddComponent<Components::Material>();

								OutlineLayer::GetActiveScene()->SetSelectedEntity(entity->GetID());
							}
							ImGui::EndMenu();
						}

						if (ImGui::BeginMenu("Light")) {
							if (ImGui::MenuItem("Directional Light")) {
								auto entity = OutlineLayer::GetActiveScene()->CreateEntity("Directional Light");

								
								entity->AddComponent<Components::DirectionalLight>();

								OutlineLayer::GetActiveScene()->SetSelectedEntity(entity->GetID());
							}

							if (ImGui::MenuItem("Point Light")) {
								auto entity = OutlineLayer::GetActiveScene()->CreateEntity("Point Light");
								auto& lig = entity->AddComponent<Components::PointLight>();

								auto& mr = entity->AddComponent<Components::MeshRenderer>();
								mr.LoadModel("Resources/models/sphere/scene.gltf");

								auto& mat = entity->AddComponent<Components::Material>();
								mat.Albedo = lig.Albedo;

								OutlineLayer::GetActiveScene()->SetSelectedEntity(entity->GetID());
							}

							if (ImGui::MenuItem("Spot Light")) {
								auto entity = OutlineLayer::GetActiveScene()->CreateEntity("Spot Light");

								entity->AddComponent<Components::SpotLight>();


								OutlineLayer::GetActiveScene()->SetSelectedEntity(entity->GetID());
							}
							ImGui::EndMenu();
						}
						
						
						if (ImGui::BeginMenu("Camera")) {
							
							if (ImGui::MenuItem("Perspective Camera")) {
								auto entity = OutlineLayer::GetActiveScene()->CreateEntity("Camera");

								entity->AddComponent<Components::PerspectiveCamera>();
								entity->AddComponent<Components::CameraController>();

								OutlineLayer::GetActiveScene()->SetSelectedEntity(entity->GetID());
							}

							ImGui::EndMenu();
						}
						ImGui::EndPopup();
					}
					ImGui::PopID();

					for (auto entity : entities)
					{
						if (!entity->IsChild()) {

							const auto& tagComp = entity->GetComponent<Components::Tag>();
							if (tagComp.tag != "__EDITOR_CAMERA__") {
								ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 10.0f });
								ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 0.0f, 8.0f });




								bool open = ImGui::TreeNodeEx(tagComp.tag.c_str(), ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_OpenOnArrow);


								//ImGui::PushID(tagComp.tag.c_str());

								//ImGui::PopID();



								if (ImGui::IsItemClicked())
								{
									OutlineLayer::GetActiveScene()->SetSelectedEntity(entity->GetID());
								}
								if (open) {
									auto children = entity->GetChildren();
									if (children.size() > 0) {
										for (auto pair : children)
										{
											auto child = pair.second;
											auto cTag = child->GetComponent<Components::Tag>();
											bool child_node = ImGui::TreeNodeEx(cTag.tag.c_str(), ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_OpenOnArrow);
											if (ImGui::IsItemClicked())
											{
												OutlineLayer::GetActiveScene()->SetSelectedEntity(child->GetID());
											}
											if (child_node) {

												ImGui::TreePop();
											}

										}
									}

									ImGui::TreePop();
								}



								//ImGui::SetNextItemWidth(winSize.x);


								ImGui::PopStyleVar(2);
							}

						}

					}

					ImGui::EndListBox();
				}

				End();
			}
		}
	}
}