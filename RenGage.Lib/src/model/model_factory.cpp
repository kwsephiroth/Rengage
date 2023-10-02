#include "../../inc/rengage.lib/model/model_factory.h"

namespace rengage::model {

	std::unique_ptr<Model> ModelFactory::load_model(const std::string& filename) {
		LOG_INFO("Loading model from path '" + filename + "'...")

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(filename.c_str(), ASSIMP_POST_PROCESS_FLAGS);

		if (scene == nullptr) {
			std::string errorMsg = "Failed to load model from path '" + filename + "' - ";
			LOG_ERROR(errorMsg + importer.GetErrorString())
			return nullptr;
		}
		
		std::unique_ptr<Model> model_ptr = build_model_from_scene(*scene);
		if (model_ptr != nullptr) {
			LOG_INFO("Model successfully loaded from path '" + filename + "'.")
		}
		else {
			std::string errorMsg = "Failed to load model from path '" + filename + "' - ";
			LOG_ERROR(errorMsg)
			return nullptr;
		}
		
		return model_ptr;
	}

	std::unique_ptr<Model> ModelFactory::build_model_from_scene(const aiScene& scene) {
		
		Model* model = new Model();
		bool success = init_meshes_from_scene(scene, *model);

		if (success) {
			//std::unique_ptr must take ownership of raw pointer before returning
			std::unique_ptr<Model> model_ptr = nullptr;
			model_ptr.reset(model);
			return model_ptr;
		}
		else {
			model = nullptr;
			delete model;
		}

		return nullptr;
	}

	bool ModelFactory::init_meshes(const aiScene& scene, Model& model) {

		//Extract positions, normals, and texture coordinates from aiScene mesh objects
		//then use that info to create RenGage mesh objects
		for (unsigned int mesh_index = 0; mesh_index < scene.mNumMeshes; ++mesh_index) {

		}
		return false;
	}

	Mesh ModelFactory::generate_rengage_mesh(const aiMesh& mesh) {

		Mesh rengage_mesh;
		auto vertices = mesh.mVertices;
		auto num_vertices = mesh.mNumVertices;

		for (unsigned int vertex_index = 0; vertex_index < num_vertices; ++vertex_index) {
			auto current_vertex = vertices[vertex_index];
			Vertex rengage_vertex;

			if (mesh.HasPositions()) {
				rengage_vertex.m_position = { current_vertex.x, current_vertex.y, current_vertex.z };
			}
			else {
				continue;
			}

			if (mesh.HasNormals()) {
				//This is safe because the size of normals array is mNumvertexices in size.
				auto current_normal = mesh.mNormals[vertex_index];
				rengage_vertex.m_normal = { current_normal.x, current_normal.y, current_normal.z };
			}

			if (mesh.HasTextureCoords(0)) {//TODO: Figure out what the texture coordinate set index is.
				//This is safe because the size of texture coordinates array is mNumvertexices in size.
				auto current_uv = mesh.mTextureCoords[0][vertex_index];
				rengage_vertex.m_uv = { current_uv.x, current_uv.y };
			}
		}

		return rengage_mesh;
	}
}