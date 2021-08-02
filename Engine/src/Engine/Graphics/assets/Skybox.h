#pragma once
#include "Cubemap.h"
#include "../buffers/VertexArray.h"
#include "Shader.h"

namespace ArcanaTools {
	class Skybox
	{
	public:
		Skybox(std::initializer_list<std::string> filepaths);
		~Skybox();

		void Draw();
		Shader* GetShader() { return m_shader; }
		static Skybox* Create(std::initializer_list<std::string> filepaths);
		Cubemap* GetIrredecentMap() { return m_irredecentMap; }
	private:
		Shader* m_shader;
		Cubemap* m_irredecentMap;
		size_t m_count;
		VertexArray* m_VAO;
		Cubemap* m_cubemap;
	};
}

