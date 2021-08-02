#pragma once

#include "../buffers/VertexArray.h"
#include "../buffers/IndexBuffer.h"

#include "Texture.h"
namespace ArcanaTools{

	class Mesh
	{
	public:
		Mesh(std::vector<Vertex3D>& vertices, std::vector<unsigned int>& indices, std::vector<Texture2D*>& textures);
		Mesh(const Mesh& _other) = default;
		Mesh& operator=(const Mesh& _other) = default;

		//void Draw(Shader& shader, Camera& camera, glm::mat4 matrix = glm::mat4(1));

		Mesh& GetMesh() { return *this; }
		VertexArray* GetVertexArrayObject() { return vao; }
		std::vector<Texture2D*>& GetTextures() { return textures; }
		std::vector<unsigned int> GetIndices(){ return indices; }

	private:
		VertexArray* vao;

		std::vector<Vertex3D> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture2D*> textures;


		// TEMPORARY 

		//glm::mat4 translation;
		//glm::mat4 rotation;
		//glm::mat4 scale;
		////---------------------------------
		//glm::mat4 transform;

	};

}
