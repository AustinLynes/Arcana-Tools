#include "Shader.h"

#include "engine/Graphics/renderers/Renderer3D.h"
#include "Platform/OpenGL/OpenGLShaderProgram.h"

namespace ArcanaTools {


	Shader* Shader::Create(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath)
	{
		switch (Renderer3D::GetAPI())
		{
		case RenderAPI::API::OPENGL:
			return new OpenGLShaderProgram(name, vertexPath, fragmentPath);
		}
		return nullptr;
	}

}