#include "IndexBuffer.h"
#include "engine/Graphics/renderers/Renderer3D.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace ArcanaTools {

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer3D::GetAPI()) {
		case RenderAPI::API::OPENGL:
			return new OpenGLIndexBuffer(indices, count);
		}
		return nullptr;
	}
}