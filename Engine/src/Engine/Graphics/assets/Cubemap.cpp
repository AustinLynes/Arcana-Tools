#include "Cubemap.h"
#include "Engine/Graphics/renderers/Renderer3D.h"

#include "Platform/OpenGL/OpenGLCubemap.h"

namespace ArcanaTools {

	Cubemap* Cubemap::Create(std::initializer_list<std::string> filepaths)
	{
		switch (Renderer3D::GetAPI())
			case RenderAPI::API::OPENGL:
				return new OpenGLCubemap(filepaths);

		return nullptr;
	}
}