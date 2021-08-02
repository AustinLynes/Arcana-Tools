#pragma once
namespace ArcanaTools {
	namespace Components {

		static int ID = 0;


		struct Light {
			glm::vec3 Albedo = { 1.0f, 1.0f, 1.0f };
			glm::vec3 Diffuse = { 1.0f, 1.0f, 1.0f };
			glm::vec3 Specular = { 1.0f, 1.0f, 1.0f };
		};

		struct PointLight : public Light {
			PointLight() : m_id(ID++){ }
			~PointLight() = default;
			PointLight(const PointLight& _other) = default;

			float Radius = 10.0f;

			const int& GetID() { return m_id; }
		private:
			int m_id;
		};

		struct DirectionalLight : public Light {
			DirectionalLight() { }
			~DirectionalLight() = default;
			DirectionalLight(const DirectionalLight& _other) = default;

			glm::vec3 Direction = { -0.2f, -1.0f, -0.3f };



		};

		struct SpotLight : public Light {
			SpotLight() : m_id(ID++) { }
			~SpotLight() = default;
			SpotLight(const SpotLight& _other) = default;
			
			glm::vec3 Direction = { 0.0f, 0.0f, 1.0f };

			float Cutoff = 0.5f;
			float OuterCutoff = 0.5f;

			float Constant = 0.5f;
			float Linear = 0.09f;
			float Quadratic = 0.032f;


			const int& GetID() { return m_id; }
		private:
			int m_id;
		};


	}
}