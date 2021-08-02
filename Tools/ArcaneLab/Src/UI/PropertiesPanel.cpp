#include "PropertiesPanel.h"


#include "../EditorLayer.h"
#include "../OutlineLayer.h"
#include <Engine/ECS/Entity/DefaultBehavior.h>

namespace ArcanaTools {
	namespace UI {
		PropertiesPanel::PropertiesPanel() : UIWindow("Properties") {}
		void PropertiesPanel::OnAttach()
		{
		}

		void PropertiesPanel::OnDetach()
		{
		}

		void PropertiesPanel::OnUpdate()
		{
		}

		void LabelText(const std::string& label, std::string& text, Entity* entity) {
			auto& tagComp = entity->GetComponent<Components::Tag>();
			std::string buffer = tagComp.tag;


			ImGui::PushID(label.c_str());
			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, 100.0f);
			ImGui::Text(label.c_str());
			ImGui::NextColumn();
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::PushItemWidth(ImGui::GetContentRegionAvailWidth());
			if (ImGui::InputText("###Tag:", &buffer, ImGuiInputTextFlags_AllowTabInput)) {}
			{
				tagComp.tag = buffer;
			}

			ImGui::PopID();
			ImGui::NextColumn();
			ImGui::Columns(1);

		}
		// -----------------------------------------------------------------
		// label | [X][  value ][Y][  value  ][Z][  value  ]
		// ---------------------------------------------------------------

		glm::vec3 Vec3Control(const std::string& label, glm::vec3& values, Entity* entity, float reset_val = 0.0f, float col_width = 100.0f) {

			// Get Transform componenet from entity
			auto& transformComp = entity->GetComponent<Components::Transform>();
			ImGui::PushID(label.c_str());

			// TELL IMGUI TO USE 2 COLUMNS 
			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, col_width);
			ImGui::Text(label.c_str());
			ImGui::NextColumn();


			ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { -12.0f,0.0f });
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 7.0f, 7.0f });

			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImVec2 buttonSize = { lineHeight * 2.0f, lineHeight };

			ImGui::PushStyleColor(ImGuiCol_Button, { 0.8f,	0.1f,	0.1f,	1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 1.0f,	0.1f,	0.1f,	1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 1.0f,	0.1f,	0.1f,	1.0f });
			if (ImGui::Button("X", buttonSize))
			{
				values.x = reset_val;
			}
			ImGui::PopStyleColor(3);
			ImGui::SameLine();
			ImGui::DragFloat("###X", &values.x, 0.1f, 0.1f);


			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 5.0f,0.0f });
			ImGui::SameLine();
			ImGui::PushStyleColor(ImGuiCol_Button, { 0.1f,	0.8f,	0.1f,	1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.1f,	1.0f,	0.1f,	1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.1f,	1.0f,	0.1f,	1.0f });

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { -12.0f,0.0f });


			if (ImGui::Button("Y", buttonSize))
			{
				values.y = reset_val;

			}
			ImGui::PopStyleColor(3);
			ImGui::SameLine();
			ImGui::DragFloat("###Y", &values.y, 0.1f, 0.1f);



			ImGui::SameLine();
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 5.0f,0.0f });
			ImGui::PushStyleColor(ImGuiCol_Button, { 0.1f,	0.1f,	0.8f,	1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.1f,	0.1f,	1.1f,	1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.1f,	0.1f,	1.1f,	1.0f });
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { -12.0f,0.0f });

			if (ImGui::Button("Z", buttonSize))
			{
				values.z = reset_val;

			}
			ImGui::SameLine();
			ImGui::PopStyleColor(3);
			ImGui::DragFloat("###Z", &values.z, 0.1f, 0.1f);
			ImGui::NextColumn();

			ImGui::PopStyleVar(6);
			ImGui::PopID();

			return values;
		}

		void PropertiesPanel::OnRender()
		{
			if (m_show) {



				if (!Begin("Properties")) {
					return;
				}

				const auto& entity = OutlineLayer::GetActiveScene()->GetSelectedEntity();
				if (entity != nullptr) {

					ImGui::Columns(2);
					
					// TAG
					auto& tagComp = entity->GetComponent<Components::Tag>();
					LabelText("Tag", tagComp.tag, entity);
					
					// TRANSFORM
					if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow)) {
						auto& transformComp = entity->GetComponent<Components::Transform>();

						auto pos = transformComp.GetPosition();
						glm::vec3 rot = transformComp.GetRotation();
						auto scale = transformComp.GetScale();




						transformComp.SetPosition(Vec3Control("Position", pos, entity));
						transformComp.SetRotation(Vec3Control("Rotation", rot, entity));
						
						if (entity->HasComponent<Components::CameraController>()) {
							auto& pc_comp = entity->GetComponent<Components::CameraController>();
							pc_comp.SetYaw(glm::radians(rot.y));
							pc_comp.SetPitch(glm::radians(rot.x));
						}

						transformComp.SetScale(Vec3Control("Scale", scale, entity, 1.0f));

					}

					// Sprite Renderer 
					if (entity->HasComponent<Components::SpriteRenderer>()) {
						auto& sr_comp = entity->GetComponent<Components::SpriteRenderer>();
						ImGui::Columns(1);
						if (ImGui::CollapsingHeader("Sprite Renderer", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow)) {
							ImGui::Columns(2);

							ImGui::Text("Tint");
							ImGui::NextColumn();
							static float col[4]{ sr_comp.TintColor.x, sr_comp.TintColor.y, sr_comp.TintColor.z, sr_comp.TintColor.w };
							if (ImGui::ColorPicker4("", col, 4)) {
								sr_comp.TintColor = { col[0],col[1],col[2],col[3] }; // <<--------FIX ME
							}
							ImGui::NextColumn();

							ImGui::Text("Texture");
							ImGui::NextColumn();
							ImGui::Image((void*)sr_comp.texture->GetTextureID(), { 128, 128 });
							ImGui::NextColumn();

						}
					}

					// Sprite Renderer 
					if (entity->HasComponent<Components::MeshRenderer>()) {
						auto& mr_comp = entity->GetComponent<Components::MeshRenderer>();
						ImGui::Columns(1);
						if (ImGui::CollapsingHeader("Mesh Renderer", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow)) {
							ImGui::Columns(2);

							ImGui::Text("Texture");
							ImGui::NextColumn();
							ImGui::Text("%s", mr_comp.GetFilepath().c_str());
							ImGui::NextColumn();

						}
					}

					// Camera 
					if (entity->HasComponent<Components::PerspectiveCamera>()) {
						auto& pc_comp = entity->GetComponent<Components::PerspectiveCamera>();
						ImGui::Columns(1);
						if (ImGui::CollapsingHeader("Perspective Camera", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow)) {
							ImGui::Columns(2);

							// MAIN 
							ImGui::Text("Main");
							ImGui::NextColumn();
							bool primary = pc_comp.GetInstance()->IsPrimaryCamera();
							if (ImGui::Checkbox("###Main", &primary)) {
								pc_comp.GetInstance()->SetPrimaryCamera(primary);
							}
							ImGui::NextColumn();

							// FOV
							ImGui::Text("Field of View");
							ImGui::NextColumn();
							float fov = pc_comp.GetInstance()->GetFieldOfView();
							if (ImGui::DragFloat("###FOV", &fov, 0.1f, 30.0f, 100.0f)) {
								pc_comp.GetInstance()->SetFieldOfView(fov);
							}

							ImGui::NextColumn();

						}
					}
					ImGui::NextColumn();
					ImGui::Columns(1);

					if (entity->HasComponent<Components::Material>()) {
						if (ImGui::CollapsingHeader("Material", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow)) {
							auto& material = entity->GetComponent<Components::Material>();
							ImGui::Columns(2);

						


							ImGui::Text("Albedo");
							ImGui::NextColumn();
							ImGui::ColorEdit3("###AMB", glm::value_ptr(material.Albedo));
							ImGui::NextColumn();

							ImGui::Text("Metalic");
							ImGui::NextColumn();
							ImGui::SliderFloat("###Mtlic", &material.Metallic, 0.0000001, 1.0f);
							ImGui::NextColumn();

							ImGui::Text("Roughness");
							ImGui::NextColumn();
							ImGui::SliderFloat("###Rph", &material.Roughness, 0.0000001, 1.0f);

							ImGui::NextColumn();

							ImGui::Text("AO");
							ImGui::NextColumn();
							ImGui::SliderFloat("###AOc", &material.AmbientOccolusion, 0.0000001, 1.0f);

							ImGui::NextColumn();

						}
					}

					// Behavior
					if (entity->HasComponent<Components::NativeBehavior>()) {

						if (ImGui::CollapsingHeader("Behavior", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow)) {
							auto& behavior = entity->GetComponent<Components::NativeBehavior>(); // hmmm... 
							if (ImGui::BeginCombo("Avalable Scripts", "Pick one")) {

								for (auto script : std::filesystem::directory_iterator(OutlineLayer::GetOutlineFilePath() + "/Scripts"))
								{
									if (ImGui::Selectable(script.path().stem().string().c_str())) {
									
									}
								}
								ImGui::EndCombo();
							}
						}
					
					}
					

					// Lights 

					if (entity->HasComponent<Components::DirectionalLight>()) {

						if (ImGui::CollapsingHeader("Point Light", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow)) {
							auto& light = entity->GetComponent<Components::DirectionalLight>();

							ImGui::Columns(2);

							ImGui::Text("Direction");
							ImGui::NextColumn();
							ImGui::InputFloat3("###Dire", glm::value_ptr(light.Direction));
							ImGui::NextColumn();


							ImGui::Text("Diffuse");
							ImGui::NextColumn();
							ImGui::ColorPicker4("###Color", glm::value_ptr(light.Diffuse));
							ImGui::NextColumn();

							ImGui::Text("Ambient");
							ImGui::NextColumn();
							ImGui::ColorPicker3("###AMB", glm::value_ptr(light.Albedo));
							ImGui::NextColumn();

							ImGui::Text("Specular");
							ImGui::NextColumn();
							ImGui::ColorPicker3("###SPC", glm::value_ptr(light.Specular));
							ImGui::NextColumn();


						}

					}

					if (entity->HasComponent<Components::PointLight>()) {

						if (ImGui::CollapsingHeader("Point Light", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow)) {
							auto& light = entity->GetComponent<Components::PointLight>();

							ImGui::Columns(2);

							// MAIN 
							ImGui::Text("Diffuse");
							ImGui::NextColumn();
							ImGui::ColorPicker4("###Color", glm::value_ptr(light.Diffuse));
							ImGui::NextColumn();

							// FOV
							ImGui::Text("Ambient");
							ImGui::NextColumn();
							ImGui::ColorPicker3("###AMB", glm::value_ptr(light.Albedo));
							ImGui::NextColumn();

							ImGui::Text("Specular");
							ImGui::NextColumn();
							ImGui::ColorPicker3("###SPC", glm::value_ptr(light.Specular));
							ImGui::NextColumn();

							ImGui::Text("Radius");
							ImGui::NextColumn();
							ImGui::SliderFloat("###Rad", &light.Radius, 0.0f, 50.0f);
							ImGui::NextColumn();


							//ImVec3 col = { light.Diffuse.r, light.Diffuse.g, light.Diffuse.b };
							
						}

					}
					
					if (entity->HasComponent<Components::SpotLight>()) {

						if (ImGui::CollapsingHeader("Spot Light", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow)) {
							auto& light = entity->GetComponent<Components::SpotLight>();

							ImGui::Columns(2);

							ImGui::Text("Direction");
							ImGui::NextColumn();
							ImGui::InputFloat3("###Dire", glm::value_ptr(light.Direction));
							ImGui::NextColumn();

							ImGui::Text("Diffuse");
							ImGui::NextColumn();
							ImGui::ColorPicker4("###Color", glm::value_ptr(light.Diffuse));
							ImGui::NextColumn();

							// FOV
							ImGui::Text("Ambient");
							ImGui::NextColumn();
							ImGui::ColorPicker3("###AMB", glm::value_ptr(light.Albedo));
							ImGui::NextColumn();

							ImGui::Text("Specular");
							ImGui::NextColumn();
							ImGui::ColorPicker3("###SPC", glm::value_ptr(light.Specular));
							ImGui::NextColumn();

							ImGui::Text("Constant");
							ImGui::NextColumn();
							ImGui::InputFloat("###Con", &light.Constant);
							ImGui::NextColumn();

							ImGui::Text("Linear");
							ImGui::NextColumn();
							ImGui::InputFloat("###Lin", &light.Linear);
							ImGui::NextColumn();

							ImGui::Text("Quadratic");
							ImGui::NextColumn();
							ImGui::InputFloat("###Qua", &light.Quadratic);
							ImGui::NextColumn();

							ImGui::Text("Cutoff");
							ImGui::NextColumn();
							ImGui::InputFloat("###Cut", &light.Cutoff);
							ImGui::NextColumn();

							ImGui::Text("Outer Cutoff");
							ImGui::NextColumn();
							ImGui::InputFloat("###OutCut", &light.OuterCutoff);
							ImGui::NextColumn();

							//ImVec3 col = { light.Diffuse.r, light.Diffuse.g, light.Diffuse.b };

						}

					}


					static bool open = false;
					if (ImGui::Button("Add Component")) {
						open = !open;
					}
					const char* components[]{ 
						"None", 
						"Sprite Renderer", 
						"Mesh Renderer", 
						"Perspective Camera", 
						"Directional Light",
						"Point Light",
						"Spot Light",
						"Material", 
						"Behavior(Script)" 
					};
					static int cur_item = 0;
					if (open) {

						ImGui::Combo("###Components", &cur_item, components, IM_ARRAYSIZE(components));

						if (ImGui::Button("Add")) {
							static int cam_count = 0;
							if (cur_item != 0) {
								switch (cur_item) 
								{
									case 1: // Sprite Renderer
										entity->AddComponent<Components::SpriteRenderer>();
										break;

									case 2: // Mesh Renderer
										entity->AddComponent<Components::SpriteRenderer>();
										break;

									case 3: // Perspective Camera 
										entity->AddComponent<Components::PerspectiveCamera>();
										if (cam_count == 0)
											entity->GetComponent<Components::PerspectiveCamera>().GetInstance()->SetPrimaryCamera(true);
										cam_count++;
										break;

									case 4:	// Directional Light
										Renderer3D::BindDirectionalLight(entity->AddComponent<Components::DirectionalLight>());
									break;
									case 5:	// Point Light
										Renderer3D::BindPointLight(entity->AddComponent<Components::PointLight>(), entity->GetComponent<Components::Transform>());
										break;
									case 6:	// Spot Light
										Renderer3D::BindSpotLight(entity->AddComponent<Components::SpotLight>(), entity->GetComponent<Components::Transform>());
										break;

									case 7: // Material
										Renderer3D::BindMaterial(entity->AddComponent<Components::Material>());
										break;
									case 8: // Native Behavior
										{
				
										}

									/*	entity->AddComponent<Components::NativeBehavior>();*/
										break;
									
								}
								open = false;
								cur_item = 0;
							}

						}
					}
				}
				End();
			}

		}




		// DISPLAY ALL COMPONENTS
		// TAG
		// TRANSFORM
		// -------------------
		// OTHER COMPONENTS
	}
}