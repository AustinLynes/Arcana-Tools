#pragma once

#include "engine/graphics/renderers/RenderAPI.h"

namespace ArcanaTools {

	class OpenGLRenderAPI : public RenderAPI
	{
		// Inherited via RenderAPI
		virtual void ClearColor(const glm::vec4& clearColor) override;
		virtual void Clear() override;
		virtual void DrawIndexed(VertexArray* vao, uint32_t count) override;
		virtual void DrawArrays(uint32_t count) override;
		virtual void SetViewport(float width, float height) override;

		virtual void SetRenderMode(RenderMode mode) override;
		
		// DEPTH TESTING
		virtual void EnableDepthTesting() override;
		virtual void SetDepthMode(DepthMode mode) override;
		virtual void DisableDepthTesting() override;
		
		// BLENDING
		virtual void EnableBlending() override;
		virtual void SetBlendFunction(BlendMode srcRGB, BlendMode dstRGB, BlendMode srcA, BlendMode dstA) override;
		virtual void DisableBlending() override;






	};
}

