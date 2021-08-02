#pragma once

#include <glad/glad.h>
#include <vector>

namespace ArcanaTools {

	class IndexBuffer
	{
	public:
		IndexBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void Delete() = 0;

		virtual uint32_t GetCount() = 0;
		
		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};


}