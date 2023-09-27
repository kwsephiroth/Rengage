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

	//TODO: Currently this is incorrect. The stored vertices aren't in correct face order. Fix this.
	bool ModelFactory::init_meshes_from_scene(const aiScene& scene, Model& model) {
		//std::cout << "mNumMeshes = " << scene.mNumMeshes << "\n";

		//Extract positions, normals, and texture coordinates from aiScene mesh objects
		//then use that info to create RenGage mesh objects
		for (unsigned int mesh_index = 0; mesh_index < scene.mNumMeshes; ++mesh_index) {
			Mesh rengage_mesh;
			auto current_mesh = scene.mMeshes[mesh_index];//Capture pointer to current aiMesh object
			auto current_verts = current_mesh->mVertices;//Capture pointer to current vertex array
			auto current_num_verts = current_mesh->mNumVertices;

			for (unsigned int vert_index = 0; vert_index < current_num_verts; ++vert_index) {
				auto current_vert = current_verts[vert_index];
				//Vertex rengage_vertex;

				if (current_mesh->HasPositions()) {
					//rengage_vertex.m_position = { current_vert.x, current_vert.y, current_vert.z };
					rengage_mesh.m_positions.push_back({ current_vert.x, current_vert.y, current_vert.z });
				}
				else {
					continue;
				}

				if (current_mesh->HasNormals()) {
					//This is safe because the size of normals array is mNumVertices in size.
					auto current_normal = current_mesh->mNormals[vert_index];
					//rengage_vertex.m_normal = { current_normal.x, current_normal.y, current_normal.z };
					rengage_mesh.m_normals.push_back({ current_normal.x, current_normal.y, current_normal.z });
				}

				if (current_mesh->HasTextureCoords(0)) {//TODO: Figure out what the texture coordinate set index is.
					//This is safe because the size of texture coordinates array is mNumVertices in size.
					auto current_uv = current_mesh->mTextureCoords[0][vert_index];
					//rengage_vertex.m_uv = { current_uv.x, current_uv.y };
					rengage_mesh.m_uvs.push_back({ current_uv.x, current_uv.y });
				}

				//rengage_mesh.m_vertices.push_back(std::move(rengage_vertex));
			}
			//Finally add newly created mesh to model's mesh collection
			//std::cout << rengage_mesh << "\n";
			//model.m_meshes.push_back(std::move(rengage_mesh));
		}
		return false;
	}
}