#pragma once
#include "Engine/Graphics/buffers/VertexArray.h"

namespace ArcanaTools {
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();

		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void Delete() override;
		virtual void AddVertexBuffer(VertexBuffer* vertexBuffer) override;
		virtual void SetIndexBuffer(IndexBuffer* vertexBuffer) override;
		virtual const std::vector<VertexBuffer*>& GetVertexBuffers() const override;
		virtual const IndexBuffer* GetIndexBuffer() const override;
		virtual IndexBuffer* GetIndexBuffer() override;
	
	private: 
		uint32_t m_ID;
		uint32_t m_vertexBufferIndex = 0;
		std::vector<VertexBuffer*> m_vertexBuffers;
		IndexBuffer* m_indexBuffer;

	
	};
}

