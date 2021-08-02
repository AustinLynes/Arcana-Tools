#pragma once
#include "Engine/Graphics/assets/Texture.h"
namespace ArcanaTools {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& filePath, bool flip);
		OpenGLTexture2D(const std::string& filePath, const char* type, uint32_t size);

		
		virtual ~OpenGLTexture2D();
	
		virtual void SetData(void* data, uint32_t size) override;
		virtual void Bind(uint32_t slot = 0) const override;
		virtual bool operator==(const Texture& _other) const override;

		OpenGLTexture2D& operator=(OpenGLTexture2D& _other);
	
		virtual uint32_t GetWidth() const override;
		virtual uint32_t GetHeight() const override;
		virtual uint32_t GetTextureID() const override;
		virtual const char* GetType() override { return m_type.c_str(); }
		virtual uint32_t GetTextureSize() override { return m_fileSize; };
		virtual void AssignTextureUnit(Shader* shader, const char* location, unsigned int texID) override;

	private:
		std::string filePath;
		
		std::string m_type;
		uint32_t m_fileSize;

		uint32_t m_unit = 0;
		uint32_t m_width =0;
		uint32_t m_height = 0;
		uint32_t m_textureID = 0;
		GLenum m_internalFormat = 0, m_dataFormat = 0;

	};

}
