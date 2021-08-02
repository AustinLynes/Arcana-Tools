#include "VertexArray.h"

#include "Engine/Graphics/renderers/Renderer3D.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace ArcanaTools {
	
	VertexArray* VertexArray::Create()
	{
		switch (Renderer3D::GetAPI()) {
		case RenderAPI::API::OPENGL:
			return new OpenGLVertexArray();
		}
		return nullptr;
	}

}