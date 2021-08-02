#include "OpenGLVertexArray.h"

namespace ArcanaTools {
	static GLenum ShaderType_To_GLType(ShaderDataType type) {
		switch (type)
		{
		case ArcanaTools::ShaderDataType::Float:return GL_FLOAT;
		case ArcanaTools::ShaderDataType::Float2:return GL_FLOAT;
		case ArcanaTools::ShaderDataType::Float3:return GL_FLOAT;
		case ArcanaTools::ShaderDataType::Float4:return GL_FLOAT;
		case ArcanaTools::ShaderDataType::Mat3:return GL_FLOAT;
		case ArcanaTools::ShaderDataType::Mat4:return GL_FLOAT;
		case ArcanaTools::ShaderDataType::Int:return GL_INT;
		case ArcanaTools::ShaderDataType::Int2:return GL_INT;
		case ArcanaTools::ShaderDataType::Int3:return GL_INT;
		case ArcanaTools::ShaderDataType::Int4:return GL_INT;
		case ArcanaTools::ShaderDataType::Bool:return GL_BOOL;
		}
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_ID);
	}
	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(m_ID);

	}
	void OpenGLVertexArray::Unbind()
	{
		glBindVertexArray(0);
	}
	void OpenGLVertexArray::Delete()
	{
		glDeleteVertexArrays(1, &m_ID);
	}
	void OpenGLVertexArray::AddVertexBuffer(VertexBuffer* vertexBuffer)
	{
		glBindVertexArray(m_ID);
		vertexBuffer->Bind();
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout) {
			switch (element.type)
			{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			{
				glEnableVertexAttribArray(m_vertexBufferIndex);
				glVertexAttribPointer(
					m_vertexBufferIndex,
					element.GetComponentCount(),
					ShaderType_To_GLType(element.type),
					element.normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void*)element.offset
				);
				m_vertexBufferIndex++;
				break;
			}
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
			case ShaderDataType::Bool:
			{
				glEnableVertexAttribArray(m_vertexBufferIndex);
				glVertexAttribIPointer(
					m_vertexBufferIndex,
					element.GetComponentCount(),
					ShaderType_To_GLType(element.type),
					layout.GetStride(),
					(const void*)element.offset
				);
				m_vertexBufferIndex++;
				break;
			}
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
			{
				uint8_t count = element.GetComponentCount();
				for (uint8_t i = 0; i < count; i++)
				{
					glEnableVertexAttribArray(m_vertexBufferIndex);
					glVertexAttribPointer(
						m_vertexBufferIndex,
						count,
						ShaderType_To_GLType(element.type),
						element.normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)(element.offset + sizeof(float) * count * i)
					);
					glVertexAttribDivisor(m_vertexBufferIndex, 1);
					m_vertexBufferIndex++;
				}
				break;
			}
			default:
				std::cout << "Unknown ShaderDataType " << std::endl;
			}
		}

		m_vertexBuffers.push_back(vertexBuffer);

	}
	void OpenGLVertexArray::SetIndexBuffer(IndexBuffer* indexBuffer)
	{
		glBindVertexArray(m_ID);
		indexBuffer->Bind();
		m_indexBuffer = indexBuffer;

	}
	const std::vector<VertexBuffer*>& OpenGLVertexArray::GetVertexBuffers() const
	{
		return m_vertexBuffers;
	}
	const IndexBuffer* OpenGLVertexArray::GetIndexBuffer() const
	{
		return m_indexBuffer;
	}
	IndexBuffer* OpenGLVertexArray::GetIndexBuffer()
	{
		return m_indexBuffer;
	}
}