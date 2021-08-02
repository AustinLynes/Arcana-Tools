#pragma once

#include "glm/glm.hpp"
#include "Engine/Graphics/buffers/VertexArray.h"

namespace ArcanaTools {

	class RenderAPI {
	public:

		enum class API {
			NONE		= 0,
			OPENGL		= 1,
			DIRECT_X	= 2,
			VULKAN		= 3
		};
		enum class RenderMode {
			NONE		= 0,
			POINTS		= 1,
			SOLID		= 2,
			WIRE_FRAME	= 3
		};
		enum class DepthMode {
			NONE = 0,
			LESS = 1,
			EQUAL = 2,
			LEQUAL = 3,
			ALWAYS = 4
		};


		//C_res = C_src * F_src + C_dst * F_dst 
		//C_src: the source color vector. This is the color output of the fragment shader.
		//C_dst: the destination color vector. This is the color vector that is currently stored in the color buffer.
		//F_src: the source factor value. Sets the impact of the alpha value on the source color.
		//F_dst: the destination factor value. Sets the impact of the alpha value on the destination color.
		enum class BlendMode {
			ZERO,   
			ONE,	
			
			SRC_COLOR,	 
			DST_COLOR,
			SRC_ALPHA,
			DST_APHA,
			CONSTANT_COLOR,
			CONSTANT_ALPHA,

			ONE_MINUS_SRC_COLOR,
			ONE_MINUS_DST_COLOR,
			ONE_MINUS_SRC_APHA,
			ON_MINUS_DST_ALPHA,
			ONE_MINUS_CONSTANT_COLOR,
			ONE_MINUS_CONSTANT_ALPHA
		};

		virtual void ClearColor(const glm::vec4& clearColor) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(VertexArray* vao, uint32_t count) = 0;
		virtual void DrawArrays(uint32_t count) = 0;

		virtual void SetViewport(float width, float height) = 0;
		virtual void SetRenderMode(RenderMode mode) = 0;
		
		// DEPTH TESTING
		virtual void EnableDepthTesting() = 0;
		virtual void SetDepthMode(DepthMode mode) = 0;
		virtual void DisableDepthTesting() = 0;

		// BLENDING
		virtual void EnableBlending() = 0;
		virtual void SetBlendFunction(BlendMode srcRGB, BlendMode dstRGB, BlendMode srcA, BlendMode dstA) = 0;
		virtual void DisableBlending() = 0;

		inline static API GetAPI() { return s_API; };
	private:
		static API s_API;

	};
}