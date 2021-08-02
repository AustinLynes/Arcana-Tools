#pragma once

#include <glad/glad.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace ArcanaTools {

	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void Bind()   = 0;
		virtual void Unbind() = 0;
		virtual void Delete() = 0;

		virtual void AddVertexBuffer(VertexBuffer* vertexBuffer) = 0;
		virtual void SetIndexBuffer(IndexBuffer* vertexBuffer) = 0;

		virtual const std::vector<VertexBuffer*>& GetVertexBuffers() const = 0;
		virtual const IndexBuffer* GetIndexBuffer() const = 0;
		virtual IndexBuffer* GetIndexBuffer() = 0;

		static VertexArray* Create();

	};


}