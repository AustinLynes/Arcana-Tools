#pragma once
#include "RenderAPI.h"

// command queue
#include "RenderCommand.h"

// render assets
#include "../assets/Shader.h"
#include "../assets/Texture.h"


// Rendering Components
#include <Engine/ECS/Components/DefaultComponents.h>

#include <array>
#include <unordered_map>

#include <Engine/ECS/Entity/Entity.h>

namespace ArcanaTools {

	class Renderer3D
	{
		
	public:

		static void Init();
		static void Shutdown();

		static void BeginScene(Entity* pCameraEntity);
		static void EndScene();


		static void StartBatch();
		static void Flush();

		static void NewBatch();
		static void DecrementTextureIndex();

	/*	static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color, int entityID=0);*/
		
		static void DrawQuad(const glm::mat4& transform, Components::SpriteRenderer& spriteRenderer, int entityID = 0);
		static void DrawModel(Components::MeshRenderer& meshRenderer, Components::Transform transform, int entityID = 0);


		static void BindMaterial(Components::Material& material);

		static void BindPointLight(Components::PointLight light, Components::Transform transform);
		static void BindDirectionalLight(Components::DirectionalLight light);
		static void BindSpotLight(Components::SpotLight light, Components::Transform transform);
		static void DrawLightModel(Components::MeshRenderer& meshRenderer, Components::Transform transform, Components::PointLight, int entityID);

		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }

		static void OnWindowResize(float width, float height);

		static void BindLightShader();
		static void BindMaterialShader();


		struct Stats {
			uint32_t DrawCount = 0;
			uint32_t QuadCount = 0;
		};
		
		static const Stats& GetStats();
		static void ResetStats();

	private:
		static VertexArray* quadVAO;
		//static Skybox m_skybox;
		Texture2D* m_shadowMap;


	};


}