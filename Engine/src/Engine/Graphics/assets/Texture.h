#pragma once

#include "Shader.h"
#include "stbi_image/stbi_image.h"

namespace ArcanaTools {

	class Texture {
	public:
		
		virtual ~Texture() = default;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetTextureID() const = 0;

		virtual void SetData(void* data, uint32_t size) = 0;
		virtual void Bind(uint32_t slot = 0) const = 0;
		virtual bool operator ==(const Texture& _other) const = 0;
		virtual const char* GetType() = 0;
		virtual uint32_t GetTextureSize() = 0;

		virtual void AssignTextureUnit(Shader* shader, const char* location, unsigned int texID) = 0;

	};


	class Texture2D : public Texture {
	public:
		static Texture2D* Create(uint32_t width, uint32_t height);
		static Texture2D* Create(const std::string& filePath, bool flip = true);
		static Texture2D* Create(const std::string& filePath, const char* texName, uint32_t size);

	};
}