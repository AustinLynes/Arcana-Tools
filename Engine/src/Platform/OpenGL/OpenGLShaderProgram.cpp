#include "OpenGLShaderProgram.h"

namespace ArcanaTools {
	namespace Util {
		std::string ReadFile(const std::string& file)
		{
			std::ifstream in(file, std::ios::binary);
			if (in) {
				std::string _file;
				// determine the size of the file to be read
				in.seekg(0, std::ios::end);
				// resize the internal array of the string to 
				// be the size of the file
				_file.resize(in.tellg());
				// move back to the begining of the file
				in.seekg(0, std::ios::beg);
				// read in all of the contents of the 
				// file into the string to be returned
				in.read(&_file[0], _file.size());
				//close the ifstream object to avoid leaks
				in.close();
				//std::cout << _file << std::endl;
				return _file;
			}
			throw(errno);
		}

		void CheckCompilation(uint32_t shader_id, std::string type)
		{
			GLint success;
			GLchar infoLog[1024];
			if (type != "program")
			{
				glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
				if (!success)
				{
					glGetShaderInfoLog(shader_id, 1024, NULL, infoLog);
					std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << std::endl
						<< infoLog << std::endl;
				}
			}
			else
			{
				glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
				if (!success)
				{
					glGetProgramInfoLog(shader_id, 1024, NULL, infoLog);
					std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << std::endl 
						<< infoLog << std::endl;
				}
			}
		}
	}

	OpenGLShaderProgram::OpenGLShaderProgram(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath)
		: m_name(name)
	{

		std::string vertBytecode = Util::ReadFile(vertexPath);
		std::string fragBytecode = Util::ReadFile(fragmentPath);
	
		const char* vSrc = vertBytecode.c_str();
		const char* fSrc = fragBytecode.c_str();

		uint32_t v_shader, f_shader;
		v_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(v_shader, 1, &vSrc, nullptr);
		glCompileShader(v_shader);
		Util::CheckCompilation(v_shader, "vertex");

		f_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(f_shader, 1, &fSrc, nullptr);
		glCompileShader(f_shader);
		Util::CheckCompilation(f_shader, "fragment");

		uint32_t g_shader = 0;


		m_ID = glCreateProgram();
		glAttachShader(m_ID, v_shader);
		glAttachShader(m_ID, f_shader);

		glLinkProgram(m_ID);
		Util::CheckCompilation(m_ID, "program");


		glDeleteShader(v_shader);
		glDeleteShader(f_shader);
	
	}

	void OpenGLShaderProgram::Bind()
	{
		glUseProgram(m_ID);
	}

	void OpenGLShaderProgram::Unbind()
	{
		glUseProgram(0);
	}

	void OpenGLShaderProgram::SetInt(const std::string& locationName, int value)
	{
		glUniform1i(glGetUniformLocation(m_ID, locationName.c_str()), value);
	}

	void OpenGLShaderProgram::SetIntArray(const std::string& locationName, int* values, uint32_t count)
	{
		glUniform1iv(glGetUniformLocation(m_ID, locationName.c_str()), count, values);
	}

	void OpenGLShaderProgram::SetFloat(const std::string& locationName, float value)
	{
		glUniform1f(glGetUniformLocation(m_ID, locationName.c_str()), value);
	}

	void OpenGLShaderProgram::SetFloat2(const std::string& locationName, const glm::vec2& value)
	{
		glUniform2f(glGetUniformLocation(m_ID, locationName.c_str()),	value.x, value.y);
	}

	void OpenGLShaderProgram::SetFloat3(const std::string& locationName, const glm::vec3& value)
	{
		glUniform3f(glGetUniformLocation(m_ID, locationName.c_str()), value.x, value.y, value.z);
	}

	void OpenGLShaderProgram::SetFloat4(const std::string& locationName, const glm::vec4& value)
	{
		glUniform4f(glGetUniformLocation(m_ID, locationName.c_str()), value.x, value.y, value.z, value.w);
	}

	void OpenGLShaderProgram::SetMat4(const std::string& locationName, const glm::mat4& value)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_ID, locationName.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	uint32_t OpenGLShaderProgram::Get()
	{
		return m_ID;
	}

	const std::string& OpenGLShaderProgram::GetName() const
	{
		return m_name;
	}

	void OpenGLShaderProgram::Delete()
	{
		glDeleteProgram(m_ID);
	}
	void OpenGLShaderProgram::SetBool(const std::string& locationName, bool value)
	{
		glUniform1i(glGetUniformLocation(m_ID, locationName.c_str()), value);
	}
}
