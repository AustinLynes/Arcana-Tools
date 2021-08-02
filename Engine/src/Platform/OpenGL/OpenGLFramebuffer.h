#pragma once
#include "Engine/Graphics/buffers/Framebuffer.h"
#include <glad/glad.h>
#include <iostream>
#include <cstdint>
#include <vector>

namespace ArcanaTools {

	class OpenGLFramebuffer : public Framebuffer 
	{
	public:
		OpenGLFramebuffer(const FrameBufferSpecification& specs);
		virtual ~OpenGLFramebuffer();

		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void Delete() override;
		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) override;

		virtual void ClearAttachment(uint32_t attachmentIndex, int value) override;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override;

		virtual const FrameBufferSpecification GetSpecification() const override;

		const uint32_t& GetRenderBuffer();
		virtual uint32_t GetDepthAttachmentRendererID() const override;
		virtual void BindDepthAttachment() override; 
		virtual void UnbindDepthAttachment() override;

	private: 

		void Invalidate();


		uint32_t m_frameBufferID;


		FrameBufferSpecification m_Specs;

		std::vector<FrameBufferTextureSpecification> m_colorAttachmentSpecifications;
		FrameBufferTextureSpecification m_DepthAttachmentSpecification = FrameBufferTextureFormat::None;
		std::vector<uint32_t> m_colorAttachments;
		uint32_t m_depthAttachment = 0;




	};

}
