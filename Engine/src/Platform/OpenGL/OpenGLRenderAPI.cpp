#include "OpenGLRenderAPI.h"

void ArcanaTools::OpenGLRenderAPI::ClearColor(const glm::vec4& clearColor)
{
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
}

void ArcanaTools::OpenGLRenderAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void ArcanaTools::OpenGLRenderAPI::DrawIndexed(VertexArray* vao, uint32_t count)
{
	vao->Bind();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	vao->Unbind();
}

void ArcanaTools::OpenGLRenderAPI::DrawArrays(uint32_t count)
{
	glDrawArrays(GL_TRIANGLES, 0, count);
}

void ArcanaTools::OpenGLRenderAPI::SetViewport(float width, float height)
{
	glViewport(0, 0, width, height);
}

void ArcanaTools::OpenGLRenderAPI::SetRenderMode(RenderMode mode)
{

	switch (mode)
	{
	case ArcanaTools::RenderAPI::RenderMode::POINTS:
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	case ArcanaTools::RenderAPI::RenderMode::SOLID:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case ArcanaTools::RenderAPI::RenderMode::WIRE_FRAME:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	}

	//std::cout << "Unsupported Render Mode Selected.." << std::endl;
}

void ArcanaTools::OpenGLRenderAPI::SetDepthMode(DepthMode mode)
{
	switch (mode)
	{
	case ArcanaTools::RenderAPI::DepthMode::LESS:glDepthFunc(GL_LESS);	break;
	case ArcanaTools::RenderAPI::DepthMode::EQUAL:glDepthFunc(GL_EQUAL); break;
	case ArcanaTools::RenderAPI::DepthMode::LEQUAL: glDepthFunc(GL_LEQUAL); break;
	case ArcanaTools::RenderAPI::DepthMode::ALWAYS: glDepthFunc(GL_ALWAYS); break;
	case ArcanaTools::RenderAPI::DepthMode::NONE:glDepthFunc(GL_NONE); break;
	}

}

void ArcanaTools::OpenGLRenderAPI::EnableDepthTesting()
{
	glEnable(GL_DEPTH_TEST);
}

void ArcanaTools::OpenGLRenderAPI::DisableDepthTesting()
{
	glDisable(GL_DEPTH_TEST);
}

void ArcanaTools::OpenGLRenderAPI::EnableBlending()
{
	glEnable(GL_BLEND);
}

static GLenum BlendModeToGLType(ArcanaTools::RenderAPI::BlendMode mode) {
	switch (mode)
	{
	case ArcanaTools::RenderAPI::BlendMode::ZERO: return GL_ZERO;
	case ArcanaTools::RenderAPI::BlendMode::ONE: return GL_ONE;
	case ArcanaTools::RenderAPI::BlendMode::SRC_COLOR: return GL_SRC_COLOR;
	case ArcanaTools::RenderAPI::BlendMode::DST_COLOR: return GL_DST_COLOR;
	case ArcanaTools::RenderAPI::BlendMode::SRC_ALPHA: return GL_SRC_ALPHA;
	case ArcanaTools::RenderAPI::BlendMode::DST_APHA: return GL_DST_ALPHA;
	case ArcanaTools::RenderAPI::BlendMode::CONSTANT_COLOR: return GL_CONSTANT_COLOR;
	case ArcanaTools::RenderAPI::BlendMode::CONSTANT_ALPHA: return GL_CONSTANT_ALPHA;
	case ArcanaTools::RenderAPI::BlendMode::ONE_MINUS_SRC_COLOR: return GL_ONE_MINUS_SRC_COLOR;
	case ArcanaTools::RenderAPI::BlendMode::ONE_MINUS_DST_COLOR: return GL_ONE_MINUS_DST_COLOR;
	case ArcanaTools::RenderAPI::BlendMode::ONE_MINUS_SRC_APHA: return GL_ONE_MINUS_SRC_ALPHA;
	case ArcanaTools::RenderAPI::BlendMode::ON_MINUS_DST_ALPHA: return GL_ONE_MINUS_DST_ALPHA;
	case ArcanaTools::RenderAPI::BlendMode::ONE_MINUS_CONSTANT_COLOR: return GL_ONE_MINUS_CONSTANT_COLOR;
	case ArcanaTools::RenderAPI::BlendMode::ONE_MINUS_CONSTANT_ALPHA: return GL_ONE_MINUS_CONSTANT_ALPHA;
	default: break;
	}
}

void ArcanaTools::OpenGLRenderAPI::SetBlendFunction(BlendMode srcRGB, BlendMode dstRGB, BlendMode srcA, BlendMode dstA)
{
	GLenum Csrc = BlendModeToGLType(srcRGB);
	GLenum Cdst = BlendModeToGLType(dstRGB);
	GLenum Fsrc = BlendModeToGLType(srcA);
	GLenum Fdst = BlendModeToGLType(dstA);
	glBlendFuncSeparate(Csrc, Cdst, Fsrc, Fdst);

}

void ArcanaTools::OpenGLRenderAPI::DisableBlending()
{
	glDisable(GL_BLEND);
}
