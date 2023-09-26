#pragma once
#include "../logging/logger_macros.h"
#include "model.h"
#include <iostream>
#include <string>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

namespace rengage::model {
	
	const unsigned int ASSIMP_POST_PROCESS_FLAGS = aiProcess_Triangulate |
												   aiProcess_GenSmoothNormals |
												   //aiProcess_FlipUVs |
												   aiProcess_JoinIdenticalVertices;
	class ModelFactory
	{
	private:
		ModelFactory() = default;
		static std::unique_ptr<Model> build_model_from_aiScene(const aiScene* scene);

	public:
		static std::unique_ptr<Model> load_model(const std::string& filename);

	};
}