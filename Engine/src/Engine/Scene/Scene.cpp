#include "Scene.h"

#include "Engine/ECS/Entity/Entity.h"
#include "../Graphics/renderers/Renderer3D.h"
#include "Engine/ECS/Components/DefaultComponents.h"

#define DEFAULT_SKYBOX_FILEPATH { "engine_assets/textures/cubemaps/skyboxes/basic/right.jpg", "engine_assets/textures/cubemaps/skyboxes/basic/left.jpg", "engine_assets/textures/cubemaps/skyboxes/basic/top.jpg", "engine_assets/textures/cubemaps/skyboxes/basic/bottom.jpg", "engine_assets/textures/cubemaps/skyboxes/basic/front.jpg", "engine_assets/textures/cubemaps/skyboxes/basic/back.jpg" }


namespace ArcanaTools {
	//Scene* Scene::ActiveScene = nullptr;

	Scene::Scene(const std::string& name)
	{
		// CREATE DEFAULT SKYBOX.... hmmm
		// TODO: change this to a Scene::LoadSkybox Method to 
		//		allow for later usage of this...
		//		and for reuse... maybe we want to change the skybox for some purpose...
		m_skybox = Skybox::Create({ "Resources/textures/sky.jpg", ""});

		// save scene name
		m_name = name;

	}

	Scene::~Scene()
	{
		// Clean up all entities
		for (size_t i = 0; i < entities.size(); i++)
		{
			delete entities[i];
		}

		delete m_skybox;

	}

	Entity* Scene::CreateEntity(const std::string& name)
	{
		Entity* entity = new Entity(m_registry.create(), this, false);
		auto& tag = entity->AddComponent<Components::Tag>();
		std::string empty = "EmptyEntity_";
		empty += std::to_string(m_count);
		tag.tag = name.empty() ? empty : name;
		auto& transform = entity->AddComponent<Components::Transform>();
		transform.SetPosition({ 0.0f, 0.0f, 0.0f });
		transform.SetScale({ 1.0f, 1.0f, 1.0f });
		entities.push_back(entity);
		m_count++;
		return entity;
	}
	Entity* Scene::CreateChildEntity(const std::string& name)
	{
		Entity* entity = new Entity(m_registry.create(), this, true);
		auto& tag = entity->AddComponent<Components::Tag>();
		std::string empty = "EmptyChildEntity_";
		empty += std::to_string(m_count);
		tag.tag = name.empty() ? empty : name;
		auto& transform = entity->AddComponent<Components::Transform>();
		transform.SetPosition({ 0.0f, 0.0f, 0.0f });
		transform.SetScale({ 1.0f, 1.0f, 1.0f });
		entities.push_back(entity);
		m_count++;
		return entity;
	}

	void Scene::Initilize() {
		// INITLIZE ALL SPRITES
		auto sr_view = m_registry.view<Components::SpriteRenderer>();
		for (auto& ent : sr_view) {
			auto& sr = sr_view.get<Components::SpriteRenderer>(ent);
			if (!sr.GetFilePath().empty())
				sr.LoadTexture();
		}


		// INITLIZE ALL MODELS
		auto mr_view = m_registry.view<Components::MeshRenderer>();
		for (auto& ent : mr_view) {
			auto& mr = mr_view.get<Components::MeshRenderer>(ent);
			if (!mr.GetFilepath().empty())
				mr.LoadModel(mr.GetFilepath().c_str());
		}
	}

	void Scene::OnRuntimeStart()
	{
		m_play = true;
		// Instantiate and Start Each Script Component Attached to 
		// Each Entity
		m_registry.view<Components::NativeBehavior>().each(
			[=](auto entity, auto& behavior)
			{
				if (!behavior.Instance) {
					behavior.Instance = behavior.InstantiateScript();
					behavior.Instance->m_entity = Entity(entity, this, false);
					behavior.Instance->Start();
				}

			});

	}

	void Scene::OnUpdateRuntime(TimeStep ts)
	{
		m_registry.view<Components::NativeBehavior>().each(
			[=](auto entity, auto& behavior)
			{
				behavior.Instance->Update(ts);
			});
	}

	void Scene::OnUpdate(TimeStep ts)
	{

		if (m_play)
		{
			OnUpdateRuntime(ts);
		}


	}
	void Scene::OnRuntimeExit()
	{
		m_play = false;
		m_registry.view<Components::NativeBehavior>().each(
			[=](auto entity, auto& behavior)
			{
				behavior.Instance->Destroy();
			});
	}


	void Scene::DrawToFramebuffer(Entity* camera)
	{
		/////////////////////////////////////////////////////////////////////////////////
		/////////// SPRITE RENDERER PASS ////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////
		Renderer3D::BeginScene(camera);
		{
			RenderCommand::EnableBlending();

			ArcanaTools::Renderer3D::ResetStats();

			auto group = m_registry.group<Components::Transform>(entt::get<Components::SpriteRenderer>);

			for (auto entity : group)
			{
				const auto& [transform, spriteRenderer] = group.get<Components::Transform, Components::SpriteRenderer>(entity);

				Renderer3D::DrawQuad(transform.GetTransform(), spriteRenderer, (int)entity);

			}

		}




		

		

		

		Renderer3D::EndScene();

		Renderer3D::BeginScene(camera);

		// LIGHT RENDER PASS
		{
			auto view = m_registry.view<Components::Transform, Components::MeshRenderer, Components::PointLight>();

			for (auto entity : view) {

				auto& tc = view.get<Components::Transform>(entity);
				auto& mr = view.get<Components::MeshRenderer>(entity);
				auto& lc = view.get<Components::PointLight>(entity);

				//Renderer3D::BindMaterialShader();
				Renderer3D::BindPointLight(lc, tc);

				//Renderer3D::BindLightShader();
				Renderer3D::DrawLightModel(mr, tc, lc, (int)entity);
			}
			auto view2 = m_registry.view<Components::Transform, Components::DirectionalLight>();

			for (auto entity : view2) {

				auto& tc = view2.get<Components::Transform>(entity);
				auto& lc = view2.get<Components::DirectionalLight>(entity);

				Renderer3D::BindDirectionalLight(lc);

			}

			auto view3 = m_registry.view<Components::Transform, Components::SpotLight>();

			for (auto entity : view3) {

				auto& tc = view3.get<Components::Transform>(entity);
				auto& lc = view3.get<Components::SpotLight>(entity);

				Renderer3D::BindSpotLight(lc, tc);

			}
		}

		// MODEL RENDER PASS
		{
			auto view = m_registry.view<Components::Transform, Components::MeshRenderer, Components::Material>();
			RenderCommand::DisableBlending();
			for (auto entity : view)
			{
				//const auto& [tc, mr] = group2.get<Components::Transform, Components::MeshRenderer>(entity);
				auto& mr = view.get<Components::MeshRenderer>(entity);
				auto& tc = view.get<Components::Transform>(entity);
				auto& mc = view.get<Components::Material>(entity);

				Renderer3D::BindMaterialShader();
				Renderer3D::BindMaterial(mc);
				Renderer3D::DrawModel(mr, tc, (int)entity);

			}
		}

		Renderer3D::EndScene();


	}

	void Scene::DeleteEntity() {

		m_registry.destroy((entt::entity)selected->GetID());

		//selected->RemoveComponent<Components::SpriteRenderer>();
		Renderer3D::DecrementTextureIndex();
		entities.erase(std::find(entities.begin(), entities.end(), selected));
		delete selected;
		selected = nullptr;
	}

	Skybox* Scene::GetSkybox()
	{
		return m_skybox;
	}

	Scene* Scene::Create(const std::string& sceneName)
	{
		return new Scene(sceneName);
	}

	std::vector<Entity*> Scene::GetAllEntities()
	{
		//for (size_t i = 0; i < entities.size(); i++)
		//{
		//	auto& tagComp = entities[i]->GetComponent<Components::Tag>();
		//	//std::cout << tagComp.tag << std::endl;
		//}
		if (m_count > 0)
			return entities;
		else
			return {};
	}


	void Scene::OnResize(float width, float height) {
		for (auto entity : entities) {
			if (entity->HasComponent<Components::PerspectiveCamera>()) {
				entity->GetComponent<Components::PerspectiveCamera>().GetInstance()->SetAspectRatio(width, height);
			}
		}
	}

	Entity* Scene::GetSelectedEntity()
	{
		return selected;
	}

	void Scene::SetSelectedEntity(int id)
	{
		for (auto entity : entities) {
			if (entity->GetID() == id) {
				selected = entity;
				return;
			}
		}

		selected = nullptr;
	}

}