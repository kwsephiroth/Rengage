#include "../../inc/rengage.lib/model/model_factory.h"

namespace rengage::model {

	std::unique_ptr<Model> ModelFactory::import_model(const std::string& filename) {
		LOG_INFO("Loading model from path '" + filename + "'...")

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(filename.c_str(), ASSIMP_POST_PROCESS_FLAGS);

		if (scene == nullptr) {
			std::string errorMsg = "Failed to load model from path '" + filename + "' - ";
			LOG_ERROR(errorMsg + importer.GetErrorString())
			return nullptr;
		}
		
		std::unique_ptr<Model> model_ptr = nullptr;
		LOG_INFO("Model successfully loaded from path '" + filename + "'.")
		return model_ptr;
	}
}