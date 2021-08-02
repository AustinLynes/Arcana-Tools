#include "OpenGLBuffer.h"
namespace ArcanaTools {

	////////////////////////////////////////////////////////////////////////////////
	// 	Vertex BUFFER ///////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
	{
		glCreateBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);

	}
	
	OpenGLVertexBuffer::OpenGLVertexBuffer(Vertex* vertices, uint32_t size)
	{
		glCreateBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(Vertex2D* vertices, uint32_t size)
	{
		glCreateBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	OpenGLVertexBuffer::OpenGLVertexBuffer(Vertex3D* vertices, uint32_t size)
	{
		glCreateBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	void OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);

	}
	void OpenGLVertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void OpenGLVertexBuffer::SetData(const void* data, uint32_t size){
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}
	const BufferLayout& OpenGLVertexBuffer::GetLayout() const
	{
		return m_layout;
	}
	void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout)
	{
		m_layout = layout;
	}

	void OpenGLVertexBuffer::Delete()
	{
		glDeleteBuffers(1, &m_ID);
	}



	////////////////////////////////////////////////////////////////////////////////
	// 	INDEX BUFFER ///////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////


	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
	{
		m_indexCount = count;

		glCreateBuffers(1, &m_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);

	}

	void OpenGLIndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);

	}
	void OpenGLIndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}
	void OpenGLIndexBuffer::Delete()
	{
		glDeleteBuffers(1, &m_ID);

	}
	uint32_t OpenGLIndexBuffer::GetCount()
	{
		return m_indexCount;
	}
}