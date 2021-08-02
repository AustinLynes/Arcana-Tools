#pragma once
#include <iostream>
#include "Engine/Graphics/assets/Cubemap.h"
#include <glad/glad.h>
#include "stbi_image/stbi_image.h"
namespace ArcanaTools{

	class OpenGLCubemap : public Cubemap
	{
	public:
		OpenGLCubemap(std::initializer_list<std::string> filepaths);

		virtual void LoadCubemap() override;
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual uint32_t GetID(int texture_slot) override;

	private:
		std::vector<uint32_t> m_IDs;

		std::vector<std::string> m_filePaths;
		
	};
}

