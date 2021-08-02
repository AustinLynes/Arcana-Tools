#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Engine/Graphics/assets/Texture.h>

namespace ArcanaTools {
	namespace Components {

		struct SpriteRenderer {
			glm::vec4 TintColor = glm::vec4(1.0f);
			Texture2D* texture = nullptr;


			SpriteRenderer() {
				m_filepath = "engine_assets/textures/whiteTexture.png";
				TintColor = { 1.0f, 1.0f, 1.0f, 1.0f };
				LoadTexture();
			}

			SpriteRenderer(glm::vec4 color) 
				: TintColor(color), texture(nullptr) {};

			SpriteRenderer(const std::string& textureFilePath, const glm::vec4& tint = glm::vec4{ 1.0f })
				: m_filepath(textureFilePath), TintColor(tint), texture(nullptr) {}


			SpriteRenderer(const SpriteRenderer& other) = default;

			void LoadTexture() {
				delete texture;
				texture = Texture2D::Create(m_filepath.c_str());
			}

		
			const std::string& GetFilePath() { return m_filepath; }
			void SetFile(const char* filepath) { m_filepath = filepath; };
		private:
			std::string m_filepath;

		};
	
	}
}