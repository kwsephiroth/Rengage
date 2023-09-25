#pragma once
#include "../logging/logger_macros.h"
#include "model.h"
#include <iostream>
#include <string>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

namespace rengage::model {
	
	const unsigned int ASSIMP_POST_PROCESS_FLAGS = aiProcess_CalcTangentSpace |
												   aiProcess_Triangulate |
												   aiProcess_JoinIdenticalVertices |
												   aiProcess_SortByPType;
	class ModelFactory
	{
	private:
		ModelFactory() = default;

	public:
		static std::unique_ptr<Model> import_model(const std::string& filename);
	};
}