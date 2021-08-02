#pragma once
#include "Engine/Graphics/assets/Model.h"
// NOTE TO SELF... 
// REQUIRED STRUCTURE FOR COMPONENTS
/*
	struct COMPONENT_NAME
		COMPONENT_CONSTRUCTOR
		COMPONENT_DESTRUCTOR
		COMPONENT_COPY_CONSTRUCTOR
		COMPONENT_ASSIGN_OPERATOR

*/
namespace ArcanaTools {
	namespace Components {
		struct MeshRenderer {
			
			MeshRenderer() { }
			~MeshRenderer() = default;
			MeshRenderer(const MeshRenderer& other) = default;


			void LoadModel(const char* _filepath) {
				filepath = _filepath;
				delete model;
				model = new Model(filepath.c_str());
			}
			const std::string& GetFilepath() { return filepath; }
			
			void SetFile(const char* file) { filepath = file; }
			Model* GetModel() { return model; }
		
		private:
			std::string filepath;
			Model* model = nullptr;
		};
	}
}