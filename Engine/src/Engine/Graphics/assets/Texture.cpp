#include "Texture.h"
#include "engine/Graphics/renderers/Renderer3D.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace ArcanaTools {

	Texture2D* Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer3D::GetAPI()) {
		case RenderAPI::API::OPENGL:
			return new OpenGLTexture2D(width, height);
		}
		return nullptr;
	}
	Texture2D* Texture2D::Create(const std::string& filePath, bool flip)
	{
		switch (Renderer3D::GetAPI()) {
		case RenderAPI::API::OPENGL:
			return new OpenGLTexture2D(filePath, flip);
		}
		return nullptr;
	}
	Texture2D* Texture2D::Create(const std::string& filePath, const char* texName, uint32_t size)
	{
		switch (Renderer3D::GetAPI()) {
		case RenderAPI::API::OPENGL:
			return new OpenGLTexture2D(filePath, texName, size);
		}
		return nullptr;;
	}
}
