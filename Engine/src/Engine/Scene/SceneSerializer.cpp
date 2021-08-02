#include "SceneSerializer.h"

#include "Engine/ECS/Entity/Entity.h"
#include "Engine/ECS/Components/DefaultComponents.h"

#include <fstream>

#include <yaml-cpp/yaml.h>


namespace YAML {
	template<>
	struct convert<glm::vec3> {
		static Node encode(const glm::vec3& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}
		static bool decode(const Node& node, glm::vec3& rhs) {
			if (!node.IsSequence() || node.size() != 3) {
				return false;
			}

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();

			return true;
		}
	};

	template<>
	struct convert<glm::vec4> {
		static Node encode(const glm::vec4& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}
		static bool decode(const Node& node, glm::vec4& rhs) {
			if (!node.IsSequence() || node.size() != 4) {
				return false;
			}

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();

			return true;
		}
	};

}

namespace ArcanaTools {

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& vec) {
		out << YAML::Flow;
		out << YAML::BeginSeq << vec.x << vec.y << vec.z << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& vec) {
		out << YAML::Flow;
		out << YAML::BeginSeq << vec.x << vec.y << vec.z << vec.w << YAML::EndSeq;
		return out;

	}

	static void SerializeEntity(YAML::Emitter& out, Entity* ent) {
		out << YAML::BeginMap;
		out << YAML::Key << "Entity" << YAML::Value << ent->GetID();
		// SEIRIALIZE EACH COMPONENT
		
		
		// TAG
		if (ent->HasComponent<Components::Tag>()) {
			out << YAML::Key << "Tag";
			out << YAML::BeginMap;

			auto& tag = ent->GetComponent<Components::Tag>().tag;
			out << YAML::Key << "Tag" << YAML::Value << tag;
			out << YAML::EndMap;

		}
		//// TRANSFORM
		if (ent->HasComponent<Components::Transform>()) {
			out << YAML::Key << "Transform";
			out << YAML::BeginMap;

			auto& tc = ent->GetComponent<Components::Transform>();
			out << YAML::Key << "Translation" << YAML::Value << tc.GetPosition();
			out << YAML::Key << "Rotation" << YAML::Value << tc.GetRotation();
			out << YAML::Key << "Scale" << YAML::Value << tc.GetScale();
			out << YAML::EndMap;

		}
		// MESH RENDERER
		if (ent->HasComponent<Components::MeshRenderer>()) {
			out << YAML::Key << "MeshRenderer";
			out << YAML::BeginMap;

			auto& mr = ent->GetComponent<Components::MeshRenderer>();
			out << YAML::Key << "filepath" << YAML::Value << mr.GetFilepath();
			out << YAML::EndMap;
		}
		// SPRITE RENDERER
		if (ent->HasComponent<Components::SpriteRenderer>()) {
			out << YAML::Key << "SpriteRenderer";
			out << YAML::BeginMap;

			auto& sr = ent->GetComponent<Components::SpriteRenderer>();
			out << YAML::Key << "filepath" << YAML::Value << sr.GetFilePath().c_str();
			out << YAML::Key << "TintColor" << YAML::Value << sr.TintColor;
			out << YAML::EndMap;
		}
		// PERSPECTIVE CAMERA
		if (ent->HasComponent<Components::PerspectiveCamera>()) {
			out << YAML::Key << "PerspectiveCamera";
			out << YAML::BeginMap;

			auto& pc = ent->GetComponent<Components::PerspectiveCamera>();
			out << YAML::Key << "Width" << YAML::Value    << pc.GetInstance()->GetWidth();
			out << YAML::Key << "Height" << YAML::Value   << pc.GetInstance()->GetHeight();
			out << YAML::Key << "FarZ" << YAML::Value     << pc.GetInstance()->GetFarClipPlane();
			out << YAML::Key << "NearZ" << YAML::Value    << pc.GetInstance()->GetNearClipPlane();
			out << YAML::Key << "Fov" << YAML::Value		<< pc.GetInstance()->GetFieldOfView();
			out << YAML::Key << "isPrimary" << YAML::Value << pc.GetInstance()->IsPrimaryCamera();
			out << YAML::Key << "isEditor" << YAML::Value      << pc.GetInstance()->IsEditorCamera();
			out << YAML::EndMap;
		}
		// CAMERA CONTROLLER
		if (ent->HasComponent<Components::CameraController>()) {
			out << YAML::Key << "CameraController";
			out << YAML::BeginMap;

			auto& cc = ent->GetComponent<Components::CameraController>();
			out << YAML::Key << "Yaw" << YAML::Value << cc.GetYaw();
			out << YAML::Key << "Pitch" << YAML::Value << cc.GetPitch();
			out << YAML::Key << "RotationSpeed" << YAML::Value << cc.GetPitch();
			out << YAML::EndMap;
		}

		if (ent->HasComponent<Components::Material>()) {
			out << YAML::Key << "Material";
			out << YAML::BeginMap;

			auto& cc = ent->GetComponent<Components::Material>();
			out << YAML::Key << "Albedo" << YAML::Value << cc.Albedo;
			out << YAML::Key << "Roughness" << YAML::Value << cc.Roughness;
			out << YAML::Key << "AO" << YAML::Value << cc.AmbientOccolusion;
			out << YAML::Key << "Metallic" << YAML::Value << cc.Metallic;
			out << YAML::EndMap;
		}

		// Lights 
		// Directional Light
		if (ent->HasComponent<Components::DirectionalLight>()) {
			out << YAML::Key << "DirectionLight";
			out << YAML::BeginMap;

			auto& pl = ent->GetComponent<Components::DirectionalLight>();
			out << YAML::Key << "Direction" << YAML::Value << pl.Direction;
			out << YAML::Key << "Diffuse" << YAML::Value << pl.Diffuse;
			out << YAML::Key << "Ambient" << YAML::Value << pl.Albedo;
			out << YAML::Key << "Specular" << YAML::Value << pl.Specular;
			out << YAML::EndMap;
		}

		// Point Light 
		if (ent->HasComponent<Components::PointLight>()) {
			out << YAML::Key << "PointLight";
			out << YAML::BeginMap;

			auto& pl = ent->GetComponent<Components::PointLight>();
			out << YAML::Key << "Diffuse" << YAML::Value << pl.Diffuse;
			out << YAML::Key << "Ambient" << YAML::Value << pl.Albedo;
			out << YAML::Key << "Specular" << YAML::Value << pl.Specular;
			out << YAML::Key << "Radius" << YAML::Value << pl.Radius;
			out << YAML::EndMap;
		}

		// Spot Light
		if (ent->HasComponent<Components::SpotLight>()) {
			out << YAML::Key << "SpotLight";
			out << YAML::BeginMap;

			auto& pl = ent->GetComponent<Components::SpotLight>();
			out << YAML::Key << "Direction" << YAML::Value << pl.Direction;
			out << YAML::Key << "Diffuse" << YAML::Value << pl.Diffuse;
			out << YAML::Key << "Ambient" << YAML::Value << pl.Albedo;
			out << YAML::Key << "Specular" << YAML::Value << pl.Specular;
			out << YAML::Key << "Constant" << YAML::Value << pl.Constant;
			out << YAML::Key << "Linear" << YAML::Value << pl.Linear;
			out << YAML::Key << "Quadratic" << YAML::Value << pl.Quadratic;
			out << YAML::Key << "Cutoff" << YAML::Value << pl.Cutoff;
			out << YAML::Key << "OuterCutoff" << YAML::Value << pl.OuterCutoff;
			out << YAML::EndMap;
		}

		// SAVE EDITOR CAMERAS POSITION

		

		out << YAML::EndMap;
	}

	SceneSerializer::SceneSerializer(Scene* scene)
		: m_Scene(scene)
	{
	}
	void SceneSerializer::Serialize(const std::string& filepath)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << m_Scene->GetName(); // CHANGE
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

		auto entities = m_Scene->GetAllEntities();
		
		for (auto& entity : entities) {
			SerializeEntity(out, entity);
		}

		out << YAML::EndSeq;
		out << YAML::EndMap;


		std::ofstream fout(filepath);
		fout << out.c_str();
		fout.close();

	}
	bool SceneSerializer::Deserialize(const std::string& filepath)
	{
		YAML::Node data = YAML::LoadFile(filepath);
		if (!data["Scene"])
			return false;
		auto entities = data["Entities"];
		std::string name;
		for (auto entity : entities)
		{
			// TAG
			auto tagComp = entity["Tag"];
			if (tagComp) {
				name = tagComp["Tag"].as<std::string>();
			}

			// DESERIALIZED ENTITY TO BE CREATED IN NEW SCENE
			Entity* dse = m_Scene->CreateEntity(name);

			// Transform Component
			auto transComp = entity["Transform"];
			if (transComp) {
				auto& tc = dse->GetComponent<Components::Transform>();
				tc.SetPosition(transComp["Translation"].as<glm::vec3>());
				tc.SetRotation(transComp["Rotation"].as<glm::vec3>());
				tc.SetScale(transComp["Scale"].as<glm::vec3>());
			}

			// Mesh Renderer Component
			auto meshRenderer = entity["MeshRenderer"];
			if (meshRenderer) {
				auto& mshRenderer = dse->AddComponent<Components::MeshRenderer>();
				mshRenderer.SetFile(meshRenderer["filepath"].as<std::string>().c_str());
			}

			// Sprite Renderer Component
			auto spriteRenderer = entity["SpriteRenderer"];
			if (spriteRenderer) {
				auto& spriteComp = dse->AddComponent<Components::SpriteRenderer>();
				spriteComp.TintColor = spriteRenderer["TintColor"].as<glm::vec4>();
				spriteComp.SetFile(spriteRenderer["filepath"].as<std::string>().c_str());
			}

			// Perspective Camera Component
			auto cameraComp = entity["PerspectiveCamera"];
			if (cameraComp) {
				auto& cc = dse->AddComponent<Components::PerspectiveCamera>();
				cc.GetInstance()->SetAspectRatio(cameraComp["Width"].as<float>(), cameraComp["Height"].as<float>());
				cc.GetInstance()->SetFarClipPlane(cameraComp["FarZ"].as<float>());
				cc.GetInstance()->SetNearClipPlane(cameraComp["NearZ"].as<float>());
				cc.GetInstance()->SetFieldOfView(cameraComp["Fov"].as<float>());
				cc.GetInstance()->SetPrimaryCamera(cameraComp["isPrimary"].as<bool>());
				cc.GetInstance()->SetEditorCamera(cameraComp["isEditor"].as<bool>());
			}


			// Camera Controller Component
			auto cameraControl = entity["CameraController"];
			if (cameraControl) {
				auto& cc = dse->AddComponent<Components::CameraController>();
				cc.SetPitch(cameraControl["Pitch"].as<float>());
				cc.SetYaw(cameraControl["Yaw"].as<float>());
				cc.SetRotationSpeed(cameraControl["RotationSpeed"].as<float>());
			}

			auto matControl = entity["Material"];
			if (matControl) {
				auto& cc = dse->AddComponent<Components::Material>();
				cc.Albedo = matControl["Albedo"].as<glm::vec3>();
				cc.Roughness = matControl["Roughness"].as<float>();
				cc.AmbientOccolusion = matControl["AO"].as<float>();
				cc.Metallic = matControl["Metallic"].as<float>();
			}

			auto direction_lightComponent = entity["DirectionLight"];
			if (direction_lightComponent) {
				auto& cc = dse->AddComponent<Components::DirectionalLight>();

				cc.Direction = direction_lightComponent["Direction"].as<glm::vec3>();
				
				cc.Diffuse = direction_lightComponent["Diffuse"].as<glm::vec3>();
				cc.Specular = direction_lightComponent["Specular"].as<glm::vec3>();
				cc.Albedo = direction_lightComponent["Ambient"].as<glm::vec3>();

			}

			auto point_lightComponent = entity["PointLight"];
			if (point_lightComponent) {
				auto& cc = dse->AddComponent<Components::PointLight>();
				
				cc.Diffuse = point_lightComponent["Diffuse"].as<glm::vec3>();
				cc.Specular = point_lightComponent["Specular"].as<glm::vec3>();
				cc.Albedo = point_lightComponent["Ambient"].as<glm::vec3>();

				cc.Radius = point_lightComponent["Radius"].as<float>();
			}

			auto spot_lightComponent = entity["SpotLight"];
			if (spot_lightComponent) {
				auto& cc = dse->AddComponent<Components::SpotLight>();

				cc.Direction = direction_lightComponent["Direction"].as<glm::vec3>();

				cc.Diffuse = spot_lightComponent["Diffuse"].as<glm::vec3>();
				cc.Specular = spot_lightComponent["Specular"].as<glm::vec3>();
				cc.Albedo = spot_lightComponent["Ambient"].as<glm::vec3>();

				cc.Constant = spot_lightComponent["Constant"].as<float>();
				cc.Linear = spot_lightComponent["Linear"].as<float>();
				cc.Quadratic = spot_lightComponent["Quadratic"].as<float>();

				cc.Cutoff = spot_lightComponent["Cutoff"].as<float>();
				cc.OuterCutoff = spot_lightComponent["OuterCutoff"].as<float>();
			}
		}

		return true;

	}
}