#include "EditorLayer.h"
#include "Engine/Window/Window.h"
#include <Engine/Graphics/renderers/RenderCommand.h>
#include "OutlineLayer.h"


Entity* EditorLayer::camera = nullptr;
Framebuffer* EditorLayer::m_FrameBuffer;

void EditorLayer::OnAttach()
{
	m_ui.push_back(new EditorViewport());

	m_ui.push_back(new AssetBrowserPanel());
	m_ui.push_back(new PropertiesPanel());
	m_ui.push_back(new SceneGraphPanel());

	FrameBufferTextureSpecification fb_texSpec_RGBA{};
	fb_texSpec_RGBA.TextureFormat = FrameBufferTextureFormat::RGBA16F;

	FrameBufferTextureSpecification fb_texSpec_RGBA_BLOOM{};
	fb_texSpec_RGBA_BLOOM.TextureFormat = FrameBufferTextureFormat::RGBA16F;
	

	FrameBufferTextureSpecification fb_texSpec_DEPTH{};
	fb_texSpec_DEPTH.TextureFormat = FrameBufferTextureFormat::DEPTH24STENCIL8;
	
	FrameBufferTextureSpecification fb_texSpec_RED{};
	fb_texSpec_RED.TextureFormat = FrameBufferTextureFormat::RED_INTEGER;

	FrameBufferSpecification specs = {};

	specs.Attachments = {  fb_texSpec_RGBA,fb_texSpec_RED,  fb_texSpec_RGBA_BLOOM,   fb_texSpec_DEPTH };
	specs.Height = 1080;
	specs.Width = 1920;
	specs.Samples = 1;
	specs.SwapChainTarget = false;

	m_FrameBuffer = Framebuffer::Create(specs);


	if (OutlineLayer::GetActiveScene()->GetAllEntities().empty()) {
		auto editorCamera = OutlineLayer::GetActiveScene()->CreateEntity("__EDITOR_CAMERA__");
		auto& cameraComp = editorCamera->AddComponent<Components::PerspectiveCamera>();
		editorCamera->AddComponent<Components::CameraController>();
		cameraComp.GetInstance()->SetEditorCamera(true);
		cameraComp.GetInstance()->SetPrimaryCamera(false);
		camera = editorCamera;
	}
	else {
		auto entities = OutlineLayer::GetActiveScene()->GetAllEntities();
		for (auto ent : entities)
		{
			if (ent->HasComponent<Components::PerspectiveCamera>()) {
				if (ent->GetComponent<Components::PerspectiveCamera>().GetInstance()->IsEditorCamera()) {
					camera = ent;
				}
			}
		}
	}


	//camera = new EditorCamera();
	//camera->Position = { 0, 5, 10 };

	//camera->SetFarClipPlane(2000.0f);

	/*auto light_entity = OutlineLayer::GetActiveScene()->CreateEntity("light");
	auto& tc = light_entity->GetComponent<Components::Transform>();
	tc.SetPosition({ 0, 2, 2 });
	auto& lightComp = light_entity->AddComponent<Components::DirectionalLight>();
	
	auto light_entity2 = OutlineLayer::GetActiveScene()->CreateEntity("light2");
	auto& tc2 = light_entity2->GetComponent<Components::Transform>();
	tc2.SetPosition({ 1, 0, 0 });
	auto& lightComp2 = light_entity2->AddComponent<Components::PointLight>();
	

	auto cube_entity = OutlineLayer::GetActiveScene()->CreateEntity("Cube_");
	cube_entity->GetComponent<Components::Transform>().SetPosition({ 0, 0, 0 });
	auto& mr = cube_entity->AddComponent<Components::MeshRenderer>();
	mr.LoadModel("Resources/models/test_cube/test_cube.gltf");
	auto& mc = cube_entity->AddComponent<Components::Material>();

	auto plane_entity = OutlineLayer::GetActiveScene()->CreateEntity("Plane_");
	plane_entity->GetComponent<Components::Transform>().SetPosition({ 0, -1, 0 });
	auto& mr_p = plane_entity->AddComponent<Components::MeshRenderer>();
	mr_p.LoadModel("Resources/models/plane/scene.gltf");
	auto& mc_c = plane_entity->AddComponent<Components::Material>();*/







	


/* 
	// --------------------------------------------------------------------------- ExampleBehavior
	class ExampleBehavior : public Behavior {
	public:

		virtual void Start() override {
		}

		virtual void Destroy() override {

		}

		virtual void Update(TimeStep time) override {
			float r = (rand() % 100) / 100.0f;
			float g = (rand() % 100) / 100.0f;
			float b = (rand() % 100) / 100.0f;
			float a = (rand() % 100) / 100.0f;
			
			if (HasComponent<Components::SpriteRenderer>()) {
				auto& sr = GetComponent<Components::SpriteRenderer>();
				sr.TintColor = { r, g, b, a };
			}

		}

	}
	// --------------------------------------------------------------------------- ExampleBehavior
*/
	Window::SetFullscreen(true);

	for (auto panel: m_ui)
	{
		panel->OnAttach();
	}

	OutlineLayer::GetActiveScene()->Initilize();
	
}

void EditorLayer::OnDetach()
{
	for (auto panel : m_ui)
	{
		panel->OnDetach();
	}
}

void EditorLayer::OnUpdate(TimeStep ts)
{

	/*userInterface.Update();*/
	for (auto panel : m_ui)
	{
		panel->OnUpdate();
	}
	OutlineLayer::GetActiveScene()->OnUpdate(ts);

	glm::vec3 direction = glm::vec3{ 0.0f };
	float cameraSpeed = 0.1f;
	float velocity = cameraSpeed * ts;
	glm::vec2 new_rot = Input::GetMousePosition();

	glm::vec3 lastPos = camera->GetComponent<Components::Transform>().GetPosition();

	if (auto ent = OutlineLayer::GetActiveScene()->GetSelectedEntity()) {
		if (Input::IsKeyPressed(Key::Delete)) {
			OutlineLayer::GetActiveScene()->DeleteEntity();
			
		}
	}


	float Yaw	= camera->GetComponent<Components::CameraController>().GetPitch();
	float Pitch = camera->GetComponent<Components::CameraController>().GetPitch();




	if (Input::IsMouseButtonPressed(Mouse::Button1)) {

		if (first) {
			last_rot = Input::GetMousePosition();

			first = false;
		}

		glm::vec3 newPos = lastPos;

		// FORWARD
		if (Input::IsKeyPressed(Key::W)) {
			direction = camera->GetComponent<Components::CameraController>().Forward();
			newPos = lastPos + direction * cameraSpeed;
			camera->GetComponent<Components::Transform>().SetPosition(newPos);

		}
		// BACKWARD
		if (Input::IsKeyPressed(Key::S)) {
			direction = -camera->GetComponent<Components::CameraController>().Forward();
			newPos = lastPos + direction * cameraSpeed;
			camera->GetComponent<Components::Transform>().SetPosition(newPos);


		}
		// LEFTWORD
		if (Input::IsKeyPressed(Key::A)) {
			//direction = { -1,0,0 };
			direction = -camera->GetComponent<Components::CameraController>().Right();
			newPos = lastPos + direction * cameraSpeed;
			camera->GetComponent<Components::Transform>().SetPosition(newPos);

		}
		// RIGHTWORD
		if (Input::IsKeyPressed(Key::D)) {
			//direction = { 1,0,0 };
			direction = camera->GetComponent<Components::CameraController>().Right();
			newPos = lastPos + direction * cameraSpeed;
			camera->GetComponent<Components::Transform>().SetPosition(newPos);

		}

		// UPWORD
		if (Input::IsKeyPressed(Key::E)) {
			direction = camera->GetComponent<Components::CameraController>().Up();

			newPos = lastPos + direction * cameraSpeed;
			camera->GetComponent<Components::Transform>().SetPosition(newPos);


		}
		// DOWNWORD
		if (Input::IsKeyPressed(Key::Q)) {
			//direction = { 0, -1,0 };
			direction = -camera->GetComponent<Components::CameraController>().Up();
			newPos = lastPos + direction * cameraSpeed;
			camera->GetComponent<Components::Transform>().SetPosition(newPos);

		}

		float deltaX = (new_rot.x - last_rot.x);
		float deltaY = (new_rot.y - last_rot.y);

		last_rot = new_rot;

		Yaw = camera->GetComponent<Components::CameraController>().GetYaw() + (deltaX * camera->GetComponent<Components::CameraController>().GetRotationSpeed() * sensitivity * ts);
		Pitch = camera->GetComponent<Components::CameraController>().GetPitch() + (deltaY * camera->GetComponent<Components::CameraController>().GetRotationSpeed() * sensitivity * ts);


		camera->GetComponent<Components::CameraController>().SetYaw(Yaw);
		camera->GetComponent<Components::CameraController>().SetPitch(Pitch);



	}
	else if (Input::IsKeyPressed(Key::LeftAlt)) {

		if (Input::IsMouseButtonPressed(Mouse::Button0)) {


		/*	float deltaX = (new_rot.x - last_rot.x);
			float deltaY = (new_rot.y - last_rot.y);
			last_rot = new_rot;

			Yaw = deltaX * sensitivity * ts;
			Pitch = deltaY * sensitivity * ts;*/

			
		}

	}

	else if (Input::IsKeyPressed(Key::Z)) {

		if (first == true) {
			wireframe = wireframe ? false : true;
		}


		first = false;
	}
	else {
		first = true;
	}



}

void EditorLayer::OnEvent(Event& _event)
{

}

void EditorLayer::OnImGuiRender()
{
	for (auto panel : m_ui)
	{
		panel->OnRender();
	}
}

void EditorLayer::OnRender()
{

	m_FrameBuffer->Bind();

	RenderCommand::ClearColor({ 0.01f,0.01f,0.01f,0.0f });
	RenderCommand::SetRenderMode(wireframe ? RenderAPI::RenderMode::WIRE_FRAME : RenderAPI::RenderMode::SOLID);
	RenderCommand::Clear();
	RenderCommand::EnableDepth();
	RenderCommand::EnableBlending();

	glm::mat4 view = glm::mat4(glm::mat3(camera->GetComponent<Components::CameraController>().GetViewMatrix(camera->GetComponent<Components::Transform>().GetPosition())));
	glm::mat4 proj = camera->GetComponent<Components::PerspectiveCamera>().GetInstance()->GetProjectionMatrix();
	auto& shader = *OutlineLayer::GetActiveScene()->GetSkybox()->GetShader();
	shader.Bind();
	shader.SetMat4("un_View", view);
	shader.SetMat4("un_Projection", proj);

	RenderCommand::SetDepthMode(RenderAPI::DepthMode::LEQUAL);

	OutlineLayer::GetActiveScene()->GetSkybox()->Draw();
	
	
	RenderCommand::SetDepthMode(RenderAPI::DepthMode::LESS);

	RenderCommand::SetBlendFunction(RenderAPI::BlendMode::SRC_ALPHA, RenderAPI::BlendMode::ONE_MINUS_SRC_APHA, RenderAPI::BlendMode::SRC_ALPHA, RenderAPI::BlendMode::ONE_MINUS_SRC_APHA);

	OutlineLayer::GetActiveScene()->DrawToFramebuffer(camera);




	m_FrameBuffer->Unbind();

}
