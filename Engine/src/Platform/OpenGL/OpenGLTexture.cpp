#include "OpenGLTexture.h"
namespace ArcanaTools {


	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: m_width(width) , m_height(height)
	{
		m_internalFormat = GL_RGBA8;
		m_dataFormat = GL_RGBA;

		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		//glTextureStorage2D(m_textureID, 1, m_internalFormat, m_width, m_height);

		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& _filePath, bool flip)
		: filePath(_filePath)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(flip);
		unsigned char* data = nullptr;
		data = stbi_load(filePath.c_str(), &width, &height, &channels, 4);
		if (data == nullptr) {
			std::cout << "Failed To Load Texture" << std::endl 
				<< filePath.c_str() << std::endl;
			return;
		}
		
		m_width = width;
		m_height = height;
		GLenum i_format = 0, d_format = 0;

		i_format = GL_RGBA8;
		d_format = GL_RGBA;

		m_internalFormat = i_format;
		m_dataFormat = d_format;

		if (!(i_format & d_format)) {
			std::cout << "Format not supported" << std::endl;
			return;
		}

		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		/*glCreateTextures(GL_TEXTURE_2D, 1, &m_textureID);
		glTextureStorage2D(m_textureID, 1, m_internalFormat, m_width, m_height);*/

		glTextureParameteri(m_textureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_textureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(m_textureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_textureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//glTextureSubImage2D(m_textureID, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
		glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, width, height, 0, m_dataFormat, GL_UNSIGNED_BYTE, data);
		//glGenerateMipmap(GL_TEXTURE_2D);

	
		stbi_image_free(data);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& filePath, const char* type, uint32_t size)
	{
		int width, height, channels;
		m_fileSize = size;
		m_type = type;

		stbi_set_flip_vertically_on_load(1);
		
		unsigned char* data = nullptr;

		data = stbi_load(filePath.c_str(), &width, &height, &channels, 4);
		if (data == nullptr) {
			std::cout << "Failed To Load Texture" << std::endl
				<< filePath.c_str() << std::endl;
			return;
		}

		m_width = width;
		m_height = height;
		GLenum i_format = 0, d_format = 0;
		//if (channels == 4) {
			i_format = GL_RGBA8;
			d_format = GL_RGBA;
	/*	}
		else if (channels == 3) {
			i_format = GL_RGB8;
			d_format = GL_RGB;
		}*/

		m_internalFormat = i_format;
		m_dataFormat = d_format;

		if (!(i_format & d_format)) {
			std::cout << "Format not supported" << std::endl;
			return;
		}

		glGenTextures(1, &m_textureID);
		glActiveTexture(GL_TEXTURE0 + m_unit);
		m_unit++;

		glBindTexture(GL_TEXTURE_2D, m_textureID);
		/*glCreateTextures(GL_TEXTURE_2D, 1, &m_textureID);
		glTextureStorage2D(m_textureID, 1, m_internalFormat, m_width, m_height);*/

		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//glTextureSubImage2D(m_textureID, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
		glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, width, height, 0, m_dataFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);


		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_textureID);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		uint32_t bpp = m_dataFormat == GL_RGBA ? 4 : 3;
		assert(size == m_width * m_height * bpp && "Data Must Be Entire Texture!");
		glTextureSubImage2D(m_textureID, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);

	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		glBindTextureUnit(slot, m_textureID);
	}

	bool OpenGLTexture2D::operator==(const Texture& _other) const
	{
		return m_textureID == ((OpenGLTexture2D&)_other).m_textureID;
	}

	OpenGLTexture2D& OpenGLTexture2D::operator=(OpenGLTexture2D& _other)
	{
		if (this != &_other) {
			m_height = _other.m_width;
			m_width = _other.m_height;
			filePath = _other.filePath;
			m_internalFormat = _other.m_internalFormat;
			m_dataFormat = _other.m_dataFormat;
			m_textureID = _other.m_textureID;
		}
		return *this;;
	}

	uint32_t OpenGLTexture2D::GetWidth() const
	{
		return m_width;
	}

	uint32_t OpenGLTexture2D::GetHeight() const
	{
		return m_height;
	}

	uint32_t OpenGLTexture2D::GetTextureID() const
	{
		return m_textureID;
	}

	void OpenGLTexture2D::AssignTextureUnit(Shader* shader, const char* location, unsigned int texID)
	{
		//auto loc = ;
		shader->Bind();
		glUniform1i(glGetUniformLocation(shader->Get(), location), texID);

	}


}

