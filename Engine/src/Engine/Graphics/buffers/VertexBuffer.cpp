#include "VertexBuffer.h"
#include "engine/Graphics/renderers/Renderer3D.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include <iostream>


namespace ArcanaTools {

	VertexBuffer* VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer3D::GetAPI())
		{
		case RenderAPI::API::OPENGL:
			return new OpenGLVertexBuffer(size);
		}
		return nullptr;
	}
	VertexBuffer* VertexBuffer::Create(Vertex* vertices, uint32_t size)
	{
		switch (Renderer3D::GetAPI())
		{
		case RenderAPI::API::OPENGL:
			return new OpenGLVertexBuffer(vertices, size);
		}
		return nullptr;
	}
	VertexBuffer* VertexBuffer::Create(Vertex2D* vertices, uint32_t size)
	{
		switch (Renderer3D::GetAPI())
		{
		case RenderAPI::API::OPENGL:
			return new OpenGLVertexBuffer(vertices, size);
		}
		return nullptr;
	}
	VertexBuffer* VertexBuffer::Create(Vertex3D* vertices, uint32_t size)
	{
		switch (Renderer3D::GetAPI())
		{
		case RenderAPI::API::OPENGL:
			return new OpenGLVertexBuffer(vertices, size);
		}
		return nullptr;
	}
}
