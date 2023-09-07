#pragma once
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <iostream>
#include <string>
#include "../logging/logger_macros.h"

namespace rengage::model {
	static bool import_model(const std::string& filename)
	{
		LOG_INFO("Loading model from path '" + filename + "'...")

		// Create an instance of the Importer class
		Assimp::Importer importer;

		// And have it read the given file with some example postprocessing
		// Usually - if speed is not the most important aspect for you - you'll
		// probably to request more postprocessing than we do in this example.
		const aiScene* scene = importer.ReadFile(filename.c_str(),
												 aiProcess_CalcTangentSpace |
												 aiProcess_Triangulate |
												 aiProcess_JoinIdenticalVertices |
												 aiProcess_SortByPType);

		// If the import failed, report it
		if (nullptr == scene) {
			LOG_ERROR(importer.GetErrorString())
			return false;
		}

		LOG_INFO("Model successfully loaded from path '" + filename + "'.")
		return true;
	}
}