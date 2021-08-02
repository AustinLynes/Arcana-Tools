#include "GameLayer.h"
#include "EditorLayer.h"
#include "OutlineLayer.h"

namespace ArcanaTools {

	Framebuffer* GameLayer::m_FrameBuffer = nullptr;

	void GameLayer::OnAttach()
	{
		m_viewport = new GameViewport();
		
		FrameBufferTextureSpecification fb_texSpec_RGBA{};
		fb_texSpec_RGBA.TextureFormat = FrameBufferTextureFormat::RGBA8;

		FrameBufferTextureSpecification fb_texSpec_DEPTH{};
		fb_texSpec_DEPTH.TextureFormat = FrameBufferTextureFormat::DEPTH24STENCIL8;

		FrameBufferSpecification specs = {};


		// ADD CAMERA CONTROLLERS TO BOTH CAMERAS AND SEE IF BUILD WORKS



		specs.Attachments = { fb_texSpec_RGBA, fb_texSpec_DEPTH };
		specs.Height = 1080;
		specs.Width = 1920;
		specs.Samples = 1;
		specs.SwapChainTarget = false;

		m_viewport->OnAttach();

		m_FrameBuffer = Framebuffer::Create(specs);
	
	}

	void GameLayer::OnDetach()
	{
		m_viewport->OnDetach();
	}

	void GameLayer::OnUpdate(TimeStep ts)
	{

	}

	void GameLayer::OnEvent(Event& _event)
	{
		if (_event.GetEventType() == Events::Type::WindowResize) {

		}
	}

	void GameLayer::OnRender()
	{
		m_FrameBuffer->Bind();

		RenderCommand::ClearColor({ 0.01f,0.01f,0.01f,0.0f });
		RenderCommand::SetRenderMode(RenderAPI::RenderMode::SOLID);
		RenderCommand::Clear();
		RenderCommand::EnableDepth();
		RenderCommand::EnableBlending();
		

		auto entities = OutlineLayer::GetActiveScene()->GetAllEntities();

		Entity* cam = nullptr;
		
		for (auto entity : entities)
		{
			if (entity->HasComponent<Components::PerspectiveCamera>() && !entity->GetComponent<Components::PerspectiveCamera>().GetInstance()->IsEditorCamera()) {
				if (entity->GetComponent<Components::PerspectiveCamera>().GetInstance()->IsPrimaryCamera()) {
					cam = entity;
					break;
				}
			}
		}
		
		if (cam) {
			// Draw the Skybox first
			glm::mat4 view = glm::mat4(glm::mat3(cam->GetComponent<Components::CameraController>().GetViewMatrix(cam->GetComponent<Components::Transform>().GetPosition())));
			glm::mat4 proj = cam->GetComponent<Components::PerspectiveCamera>().GetInstance()->GetProjectionMatrix();
			auto& shader = *OutlineLayer::GetActiveScene()->GetSkybox()->GetShader();
			shader.Bind();
			shader.SetMat4("un_View", view);
			shader.SetMat4("un_Projection", proj);
			// Skybox requires F(lEqual) blending
			RenderCommand::SetDepthMode(RenderAPI::DepthMode::LEQUAL);
			OutlineLayer::GetActiveScene()->GetSkybox()->Draw();


			// Draw Other Objects in Scene
			// They Require F(Less) Blending
			RenderCommand::SetDepthMode(RenderAPI::DepthMode::LESS);
			RenderCommand::SetBlendFunction(RenderAPI::BlendMode::SRC_ALPHA, RenderAPI::BlendMode::ONE_MINUS_SRC_APHA, RenderAPI::BlendMode::SRC_ALPHA, RenderAPI::BlendMode::ONE_MINUS_SRC_APHA);
	
			OutlineLayer::GetActiveScene()->DrawToFramebuffer(cam);

	
		}


		m_FrameBuffer->Unbind();
	}

	void GameLayer::OnImGuiRender()
	{
		m_viewport->OnRender();
	}

}