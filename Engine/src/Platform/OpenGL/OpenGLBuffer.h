#pragma once
#include "Engine/Graphics/buffers/VertexBuffer.h"
#include "Engine/Graphics/buffers/IndexBuffer.h"

namespace ArcanaTools {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(uint32_t size);
		//OpenGLVertexBuffer(Vertex* vertices, uint32_t size);
		OpenGLVertexBuffer(Vertex* vertices, uint32_t size);
		OpenGLVertexBuffer(Vertex2D* vertices, uint32_t size);
		OpenGLVertexBuffer(Vertex3D* vertices, uint32_t size);


		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Delete() override;

		virtual void SetData(const void* data, uint32_t size) override;
		
		virtual const BufferLayout& GetLayout() const override;
		virtual void SetLayout(const BufferLayout& layout) override ;


	private:
		uint32_t m_ID;
		BufferLayout m_layout;
	};


	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);

		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void Delete() override;

		virtual uint32_t GetCount() override;

	private:
		uint32_t m_ID;
		uint32_t m_indexCount;
	};

}
