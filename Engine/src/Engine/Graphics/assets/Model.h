#pragma once

#include <json/json.hpp>
#include"Mesh.h"

using json = nlohmann::json;

namespace ArcanaTools {

	class Model
	{
	public:
		// Loads in a model from a file and stores tha information in 'data', 'JSON', and 'file'
		Model(const char* file);
		~Model(){}
		Model(const Model& _other) {
			*this = _other;
		}
		Model& operator=(const Model& _other) {
			if (this != &_other) {
				this->file = _other.file;
				this->data = _other.data;
				this->JSON = _other.JSON;
				
				// might need to deep copy these...
				this->meshes = _other.meshes;
				this->translationsMeshes = _other.translationsMeshes;
				this->rotationsMeshes = _other.rotationsMeshes;
				this->scalesMeshes = _other.scalesMeshes;
				this->matricesMeshes = _other.matricesMeshes;

				this->loadedTexName = _other.loadedTexName;
				this->loadedTex = _other.loadedTex;
			}
			return *this;
		}
		//void Draw(Shader& shader, Camera& camera);
		
		/*void SetTransform(float posX, float posY, float posZ);
		void SetRotation(float degrees, glm::vec3 axis);
		void SetScale(float x, float y, float z);

		glm::vec3 GetTransform();
		glm::vec3 GetRotation();
		glm::vec3 GetScale();*/

		std::vector<Mesh> GetMeshes() { return meshes; }
	
	private: 
		// Loads a single mesh by its index
		void loadMesh(unsigned int indMesh);

		// Traverses a node recursively, so it essentially traverses all connected nodes
		void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

		// Gets the binary data from a file
		std::vector<unsigned char> getData();
		
		// 
		std::vector<Texture2D*> GetTextures();

		// Interprets the binary data into floats, indices, and textures
		std::vector<float> getFloats(json accessor);
		std::vector<GLuint> getIndices(json accessor);

		// Assembles all the floats into vertices
		std::vector<Vertex3D> AssembleVertices(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<glm::vec2> texUVs );

		// Helps with the assembly from above by grouping floats
		std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
		std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
		std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);
	
	private: // MEMBERS
		// Variables for easy access
		const char* file;
		std::vector<unsigned char> data;
		json JSON;

		// All the meshes and transformations
		std::vector<Mesh> meshes;
		std::vector<glm::vec3> translationsMeshes;
		std::vector<glm::quat> rotationsMeshes;
		std::vector<glm::vec3> scalesMeshes;
		std::vector<glm::mat4> matricesMeshes;

		// Prevents textures from being loaded twice
		std::vector<std::string> loadedTexName;
		std::vector<Texture2D*> loadedTex;

		
	};
}
