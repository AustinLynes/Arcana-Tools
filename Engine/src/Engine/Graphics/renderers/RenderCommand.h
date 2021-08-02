#pragma once
#include "RenderAPI.h"
#include <Platform/OpenGL/OpenGLRenderAPI.h>

namespace ArcanaTools {
	
	class RenderCommand {
	public:
		// Viewport
		inline static void SetViewport(float width, float height) { s_RenderAPI->SetViewport(width, height); }
		
		// Drawing
		inline static void ClearColor(const glm::vec4& color) { s_RenderAPI->ClearColor(color); }
		inline static void Clear()  { s_RenderAPI->Clear(); }
		inline static void DrawIndexed(VertexArray* vao, uint32_t count) { s_RenderAPI->DrawIndexed(vao, count); }
		inline static void DrawArrays(uint32_t count) { s_RenderAPI->DrawArrays(count);}
		
		// RASTERIZER
		inline static void SetRenderMode(RenderAPI::RenderMode mode) { s_RenderAPI->SetRenderMode(mode); }
		
		// DEPTH TESTING
		inline static void EnableDepth() { s_RenderAPI->EnableDepthTesting(); }
		inline static void SetDepthMode(RenderAPI::DepthMode mode)  { s_RenderAPI->SetDepthMode(mode); }
		inline static void DisableDepth() { s_RenderAPI->DisableDepthTesting(); }
		
		// BLENDING
		inline static void EnableBlending() { s_RenderAPI->EnableBlending(); }
		inline static void SetBlendFunction(RenderAPI::BlendMode C, RenderAPI::BlendMode D, RenderAPI::BlendMode Ca = RenderAPI::BlendMode::ONE, RenderAPI::BlendMode Da = RenderAPI::BlendMode::ZERO) { s_RenderAPI->SetBlendFunction(C, D, Ca, Da); }
		inline static void DisableBlending() { s_RenderAPI->DisableBlending(); }


	private:
		static RenderAPI* s_RenderAPI;
	};
}