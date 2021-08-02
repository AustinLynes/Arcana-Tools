#pragma once
#include <vector>
#include <string>

namespace ArcanaTools {
	class Cubemap {
	public:
		virtual ~Cubemap() = default;
		
		virtual void LoadCubemap() = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual uint32_t GetID(int texture_slot = 0) = 0;

		static Cubemap* Create(std::initializer_list<std::string> faceFilePaths);
	};
}