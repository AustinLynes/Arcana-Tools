#pragma once
#include <glm/glm.hpp>

namespace ArcanaTools{
	namespace Components {
		struct Material {

			Material(){}
			~Material() = default;
			Material(const Material& other) = default;

			
			glm::vec3 Albedo = { 1.0f, 1.0f, 1.0f };
			float Roughness = 0.5f;
			float Metallic = 0.2f;
			float AmbientOccolusion = 0.2f;
		};
	}
}