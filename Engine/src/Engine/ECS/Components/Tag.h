#pragma once
#include <string>

namespace ArcanaTools {
	namespace Components {
		struct Tag {
			std::string tag = "";

			Tag() = default;
			Tag(std::string _tag) : tag(_tag) {}
			Tag(const Tag& other) = default;

		};

	}
}