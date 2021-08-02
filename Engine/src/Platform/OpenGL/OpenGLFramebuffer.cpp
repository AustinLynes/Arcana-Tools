#include "OpenGLFramebuffer.h"

namespace ArcanaTools {

	static const uint32_t MAX_FRAMEBUFFER_SIZE = 8192;
	namespace Util {
		static GLenum TextureTarget(bool multisampled) {
			return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
		}
		static void CreateTextures(bool multisampled, uint32_t* outID, uint32_t count) {
			glCreateTextures(TextureTarget(multisampled), count, outID);
		}
		static void BindTexture(bool multisampled, uint32_t id) {
			glBindTexture(TextureTarget(multisampled), id);
		}
		static void AttachColorTexture(uint32_t id, int samples, GLenum internalFormat, GLenum format, uint32_t width, uint32_t height, int index) {
			bool multisampled = samples > 1;
			if (multisampled) {
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);
			}
			else {
				glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), id, 0);
		}
		static void AttachDepthTexture(uint32_t id, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height)
		{
			bool multisampled = samples > 1;
			if (multisampled) {
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
			}
			else {
				glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), id, 0);
		}
		static bool IsDepthFormat(FrameBufferTextureFormat format) {
			switch (format)
			{
				case ArcanaTools::FrameBufferTextureFormat::DEPTH24STENCIL8: return true;
			}
			return false;
		}
		//static bool IsDepthFormat(FrameBufferTextureFormat format) {
		//	switch (format)
		//	{
		//	case Engine::FrameBufferTextureFormat::DEPTH24STENCIL8: return true;
		//	}
		//	return false;
		//}

		static GLenum FormatToGLType(FrameBufferTextureFormat format) {
			switch (format)
			{
			case ArcanaTools::FrameBufferTextureFormat::None:return GL_NONE;
			case ArcanaTools::FrameBufferTextureFormat::RGBA8: return GL_RGBA8;
			case ArcanaTools::FrameBufferTextureFormat::RGBA16F: return GL_RGB16F;
			case ArcanaTools::FrameBufferTextureFormat::RED_INTEGER: return GL_RED_INTEGER;
			}

			return 0;
		}

	}
	OpenGLFramebuffer::OpenGLFramebuffer(const FrameBufferSpecification& specs)
		: m_Specs(specs)
	{
		for (auto spec : m_Specs.Attachments.Attachments)
		{
			if (!Util::IsDepthFormat(spec.TextureFormat)) {
				m_colorAttachmentSpecifications.emplace_back(spec);
			}
			else
			{
				m_DepthAttachmentSpecification = spec;
			}

			Invalidate();
		}
	}


	void OpenGLFramebuffer::Invalidate() {

		if (m_frameBufferID) {
			glDeleteFramebuffers(1, &m_frameBufferID);
			glDeleteTextures(m_colorAttachments.size(), m_colorAttachments.data());
			glDeleteTextures(1, &m_depthAttachment);

			m_colorAttachments.clear();
			m_depthAttachment = 0;
		}

		glCreateFramebuffers(1, &m_frameBufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);

		//glCreateFramebuffers(1, &m_depthAttachment);
		//glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);


		bool multisample = m_Specs.Samples > 1;

		if (m_colorAttachmentSpecifications.size()) {
			m_colorAttachments.resize(m_colorAttachmentSpecifications.size());
			Util::CreateTextures(multisample, m_colorAttachments.data(), m_colorAttachments.size());

			for (size_t i = 0; i < m_colorAttachments.size(); i++)
			{
				Util::BindTexture(multisample, m_colorAttachments[i]);
				switch (m_colorAttachmentSpecifications[i].TextureFormat)
				{
				case FrameBufferTextureFormat::RGBA8:
					Util::AttachColorTexture(m_colorAttachments[i], m_Specs.Samples, GL_RGBA8, GL_RGBA, m_Specs.Width, m_Specs.Height, i);
					break;
				case FrameBufferTextureFormat::RGBA16F:
					Util::AttachColorTexture(m_colorAttachments[i], m_Specs.Samples, GL_RGB16F, GL_RGBA, m_Specs.Width, m_Specs.Height, i);
					break;
				case FrameBufferTextureFormat::RED_INTEGER:
					Util::AttachColorTexture(m_colorAttachments[i], m_Specs.Samples, GL_R32I, GL_RED_INTEGER, m_Specs.Width, m_Specs.Height, i);
					break;

				}

			}
		}


		if (m_DepthAttachmentSpecification.TextureFormat != FrameBufferTextureFormat::None) {
			Util::CreateTextures(multisample, &m_depthAttachment, 1);
			Util::BindTexture(multisample, m_depthAttachment);
			switch (m_DepthAttachmentSpecification.TextureFormat)
			{
			case FrameBufferTextureFormat::DEPTH24STENCIL8:
				Util::AttachDepthTexture(m_depthAttachment, m_Specs.Samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_Specs.Width, m_Specs.Height);
				break;
			}
		}


		if (m_colorAttachments.size() > 1) {
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1,GL_COLOR_ATTACHMENT2,GL_COLOR_ATTACHMENT3 };
			glDrawBuffers(m_colorAttachments.size(), buffers);
		}
		else if (m_colorAttachments.empty()) {
			glDrawBuffer(GL_NONE);
		}

	}

	void OpenGLFramebuffer::UnbindDepthAttachment()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

	uint32_t OpenGLFramebuffer::GetDepthAttachmentRendererID() const
	{
		return m_depthAttachment;
	}

	void OpenGLFramebuffer::BindDepthAttachment()
	{

	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_frameBufferID);
		glDeleteTextures(m_colorAttachments.size(), m_colorAttachments.data());
		glDeleteTextures(1, &m_depthAttachment);
		
	}
	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);
		glViewport(0, 0, m_Specs.Width, m_Specs.Height);
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Delete()
	{
		glDeleteFramebuffers(1, &m_frameBufferID);
		glDeleteTextures(m_colorAttachments.size(), m_colorAttachments.data());
		glDeleteTextures(1, &m_depthAttachment);
	}

	const uint32_t& OpenGLFramebuffer::GetRenderBuffer()
	{
		return 0;
	}

	void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
	{
		m_Specs.Width = width;
		m_Specs.Height = height;
		glViewport(0, 0, m_Specs.Width, m_Specs.Height);
		Invalidate();
	}

	int OpenGLFramebuffer::ReadPixel(uint32_t attachmentIndex, int x, int y)
	{
		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
		int pixelData = -1;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
		return pixelData;
	}

	void OpenGLFramebuffer::ClearAttachment(uint32_t attachmentIndex, int value)
	{
		auto& spec = m_colorAttachmentSpecifications[attachmentIndex];
		glClearTexImage(m_colorAttachments[attachmentIndex], 0, Util::FormatToGLType(spec.TextureFormat), GL_INT, &value);
	}

	uint32_t OpenGLFramebuffer::GetColorAttachmentRendererID(uint32_t index) const
	{
		return m_colorAttachments[index];
	}

	const FrameBufferSpecification OpenGLFramebuffer::GetSpecification() const
	{
		return m_Specs;
	}

}