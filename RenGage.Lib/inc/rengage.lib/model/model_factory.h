#pragma once
#include "../services/logging/logger_macros.h"
#include "model.h"
#include <iostream>
#include <string>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <boost/di.hpp> // TODO: Determine if this is still needed.
#include <filesystem>

namespace rengage::model {

	const unsigned int ASSIMP_POST_PROCESS_FLAGS = aiProcess_Triangulate |
		aiProcess_GenSmoothNormals |
		aiProcess_FlipUVs |
		aiProcess_JoinIdenticalVertices;

	class ModelFactory
	{
	private:
		std::shared_ptr<OGLInvoker> m_ogl_invoker;
		std::shared_ptr<services::logging::ILogger> m_logger;

		std::unique_ptr<Model> build_model_from_scene(const aiScene& scene, const ModelParameters& params);
		bool init_meshes(const aiScene& scene, Model& model);
		bool init_textures(const aiMaterial& ai_material, Model& model, Mesh& mesh, std::filesystem::path textures_dir="");
		void process_node(const aiNode& node, const aiScene& scene, Model& model);
		Mesh generate_rengage_mesh(const aiMesh& ai_mesh);

	public:
		explicit ModelFactory(std::shared_ptr<OGLInvoker> ogl_invoker, std::shared_ptr<services::logging::ILogger> logger);
		std::unique_ptr<Model> load_model(const ModelParameters& params);
	};
}