#pragma once
#include "Engine/Graphics/assets/Shader.h"

namespace ArcanaTools {

	class OpenGLShaderProgram : public Shader
	{

	public:
		OpenGLShaderProgram(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);

		virtual void Bind() override;
		virtual void Unbind() override;
	
		virtual void SetInt(const std::string& locationName, int value) override;
		virtual void SetIntArray(const std::string& locationName, int* values, uint32_t count) override;
		virtual void SetFloat(const std::string& locationName, float value) override;
		virtual void SetFloat2(const std::string& locationName, const glm::vec2& value) override;
		virtual void SetFloat3(const std::string& locationName, const glm::vec3& value) override;
		virtual void SetFloat4(const std::string& locationName, const glm::vec4& value) override;
		virtual void SetMat4(const std::string& locationName, const glm::mat4& value) override;
		
		virtual uint32_t Get() override;

		virtual const std::string& GetName() const override;
		virtual void Delete() override;
	
	private:
		uint32_t m_ID;
		std::string m_name;


		// Inherited via Shader
		virtual void SetBool(const std::string& locationName, bool value) override;

	};
}

