#include "Mesh.h"

namespace ArcanaTools {

	Mesh::Mesh(std::vector<Vertex3D>& _vertices, std::vector<unsigned int>& _indices, std::vector<Texture2D*>& _textures)
	{
		vertices = _vertices;

		indices = _indices;
		textures = _textures;
		
		
		VertexBuffer* vertexBuffer = VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(Vertex3D));
		vertexBuffer->Bind();
		BufferLayout layout = {
			{ShaderDataType::Float3, "v_position"},
			{ShaderDataType::Float3, "v_normal"},
			{ShaderDataType::Float3, "v_color"},
			{ShaderDataType::Float2, "v_uv"},
		};

		vertexBuffer->SetLayout(layout);

		vao = VertexArray::Create();
		vao->Bind();
		vao->AddVertexBuffer(vertexBuffer);

		IndexBuffer* indexBuffer = IndexBuffer::Create(indices.data(), indices.size());
		vao->SetIndexBuffer(indexBuffer);
		
	}

	//void Mesh::Draw(Shader& shader, Camera& camera, glm::mat4 matrix)
	//{
	//	//shader.Activate();
	//	vao.Bind();

	//	// keep track of the number of texture types we have
	//	unsigned int diff_count = 0;
	//	unsigned int spec_count = 0;
	//	//std::cout << textures.size() << std::endl;

	//	for (unsigned int i = 0; i < textures.size(); i++)
	//	{
	//		std::string num;
	//		std::string type = textures[i].GetType();

	//		if (type == "diffuse") {
	//			num = std::to_string(diff_count++);
	//		}
	//		else if (type == "specular") {
	//			num = std::to_string(spec_count++);

	//		}

	//		textures[i].AssignTextureUnit(shader, (type + num).c_str(), i);
	//		textures[i].Bind();
	//	}

	//	glUniform3f(glGetUniformLocation(shader.Get(), "camPos"), 
	//		camera.m_position.x, camera.m_position.y, camera.m_position.z
	//	);
	//	//camera.UpdateShaderUniform(shader,);

	//	// Initialize matrices
	//	glm::mat4 trans = glm::mat4(1.0f);
	//	//glm::mat4 rot = glm::mat4(1.0f);
	//	glm::mat4 sca = glm::mat4(1.0f);

	//	// Transform the matrices to their correct form
	//	trans = glm::translate(trans, m_translation);
	//	//rot = m_rotation;
	//	sca = glm::scale(sca, m_scale);
	//	//glUniformMatrix4fv(glGetUniformLocation(shader.Get(), "view_projection"), 1, GL_FALSE, glm::value_ptr(trans));



	//	// Push the matrices to the vertex shader
	//	glUniformMatrix4fv(glGetUniformLocation(shader.Get(), "translation"), 1, GL_FALSE, glm::value_ptr(trans));
	//	glUniformMatrix4fv(glGetUniformLocation(shader.Get(), "rotation"), 1, GL_FALSE, glm::value_ptr(m_rotation));
	//	glUniformMatrix4fv(glGetUniformLocation(shader.Get(), "scale"), 1, GL_FALSE, glm::value_ptr(sca));
	//	glUniformMatrix4fv(glGetUniformLocation(shader.Get(), "model"), 1, GL_FALSE, glm::value_ptr(matrix));


	//	std::cout << indices.size() << std::endl;
	//	// Draw the actual mesh
	//	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	//}

}
