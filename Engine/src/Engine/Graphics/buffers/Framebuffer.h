#pragma once
#include <iostream>
#include <cstdint>
#include "vector"

namespace ArcanaTools {
	enum class FrameBufferTextureFormat {
		None,
		RGBA8,
		RGBA16F,
		RED_INTEGER,

		DEPTH24STENCIL8,

		//defaults 
		Color = RGBA8,
		Depth = DEPTH24STENCIL8
	};

	struct FrameBufferTextureSpecification {
		FrameBufferTextureSpecification() = default;
		FrameBufferTextureSpecification(FrameBufferTextureFormat format) : TextureFormat(format) {};
		FrameBufferTextureFormat TextureFormat = FrameBufferTextureFormat::None;
	};

	struct FrameBufferAttachmentSpecification {
		FrameBufferAttachmentSpecification() = default;
		FrameBufferAttachmentSpecification(std::initializer_list<FrameBufferTextureSpecification > attachments) : Attachments(attachments) {};
		std::vector<FrameBufferTextureSpecification> Attachments;
	};

	struct FrameBufferSpecification {
		uint32_t Width = 0, Height = 0;
		FrameBufferAttachmentSpecification Attachments;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual void Bind() =0;
		virtual void Unbind() = 0;

		virtual void BindDepthAttachment() = 0;
		virtual void UnbindDepthAttachment() = 0;
		
		virtual void Resize(uint32_t width, uint32_t height) = 0;
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) = 0;
		virtual void ClearAttachment(uint32_t attachmentIndex, int value) = 0;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0;
		virtual uint32_t GetDepthAttachmentRendererID() const = 0;
		
		virtual const FrameBufferSpecification GetSpecification() const = 0;

		virtual void Delete() = 0;
		
	
		static Framebuffer* Create(const FrameBufferSpecification& specs);


	};
}

