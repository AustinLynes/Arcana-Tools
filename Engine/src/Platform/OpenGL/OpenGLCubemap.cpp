#include "OpenGLCubemap.h"

namespace ArcanaTools {

	OpenGLCubemap::OpenGLCubemap(std::initializer_list<std::string> filepaths) : m_filePaths(filepaths) { LoadCubemap(); }
	
	
	void OpenGLCubemap::LoadCubemap()
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		m_IDs.resize(m_filePaths.size());

		for (int i = 0; i < m_filePaths.size(); i++)
		{
			static bool cube = m_filePaths.size() > 2;

			glGenTextures(1, &m_IDs[i]);
			glBindTexture(cube ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D, m_IDs[i]);


			float* data = stbi_loadf(m_filePaths[i].c_str(), &width, &height, &channels, 0);
			if (data) {
				glTexImage2D(cube ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data);
				stbi_image_free(data);
			}
			else {
				std::cout << "CUBEMAP FAILED TO LOAD TEXTURE \n" << m_filePaths[i] << std::endl;
				stbi_image_free(data);
			}
		
			glTexParameteri(cube ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(cube ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(cube ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(cube ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			
		}
	}
	void OpenGLCubemap::Bind()

	{
		static bool cube = m_filePaths.size() > 2;

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(cube ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D, m_IDs[1]);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_IDs[0]);
	}
	void OpenGLCubemap::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	uint32_t OpenGLCubemap::GetID(int texture_slot)
	{
		return m_IDs[texture_slot];
	}
}
