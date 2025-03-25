#pragma once
#include "../logging/logger_macros.h"
#include "model.h"
#include <iostream>
#include <string>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <boost/di.hpp>

namespace rengage::model {
	
	const unsigned int ASSIMP_POST_PROCESS_FLAGS = aiProcess_Triangulate |
												   aiProcess_GenSmoothNormals |
												   aiProcess_FlipUVs |
												   aiProcess_JoinIdenticalVertices;
	class ModelFactory
	{
	private:
		std::shared_ptr<OGLInvoker> m_ogl_invoker;
		std::shared_ptr<ILogger> m_logger;

		std::unique_ptr<Model> build_model_from_scene(const aiScene& scene);
		bool init_meshes(const aiScene& scene, Model& model);
		bool init_textures(const aiScene& scene, Model& model);
		void process_node(const aiNode& node, const aiScene& scene, Model& model);
		Mesh generate_rengage_mesh(const aiMesh& ai_mesh);

	public:
		explicit ModelFactory(std::shared_ptr<OGLInvoker> ogl_invoker, std::shared_ptr<ILogger> logger);
		std::unique_ptr<Model> load_model(const std::string& filename,
										  const GLint position_index,
										  const GLint normal_index,
										  const GLint tex_coord_index,
										  std::optional<GLuint> VAO=std::nullopt);
	};
}