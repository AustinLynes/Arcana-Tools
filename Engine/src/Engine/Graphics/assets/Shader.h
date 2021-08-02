#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ArcanaTools {

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void SetInt(const std::string& locationName, int value) = 0;
		virtual void SetBool(const std::string& locationName, bool value) = 0;
		virtual void SetIntArray(const std::string& locationName, int* values, uint32_t count) = 0;
		virtual void SetFloat(const std::string& locationName, float value) = 0;
		virtual void SetFloat2(const std::string& locationName, const glm::vec2& value) = 0;
		virtual void SetFloat3(const std::string& locationName, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string& locationName, const glm::vec4& value) = 0;
		virtual void SetMat4(const std::string& locationName, const glm::mat4& value) = 0;

		virtual uint32_t Get() = 0;


		virtual const std::string& GetName() const = 0;
		
		virtual void Delete() = 0;

		static Shader* Create(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);


	};


}