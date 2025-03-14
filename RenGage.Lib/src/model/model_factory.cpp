#include "../../inc/rengage.lib/model/model_factory.h"

namespace rengage::model {

	ModelFactory::ModelFactory(std::shared_ptr<OGLInvoker> ogl_invoker, std::shared_ptr<ILogger> logger) :
		m_ogl_invoker(std::move(ogl_invoker)),
		m_logger(std::move(logger))
	{
	}

	std::unique_ptr<Model> ModelFactory::load_model(const std::string& filename,
													const GLint position_index,
													const GLint normal_index,
													const GLint tex_coord_index,
													std::optional<GLuint> VAO)
	{
		LOG_INFO(m_logger, "Loading model from path '" + filename + "'...")

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(filename.c_str(), ASSIMP_POST_PROCESS_FLAGS);

		if (scene == nullptr) {
			std::string errorMsg = "Failed to load model from path '" + filename + "' - ";
			LOG_ERROR(m_logger, errorMsg + importer.GetErrorString())
			return nullptr;
		}
		
		std::unique_ptr<Model> model_ptr = build_model_from_scene(*scene);
		if (model_ptr != nullptr) {
			//Bind VAO then bind and setup mesh VBOs
			if (VAO.has_value()) {
				model_ptr->setup_VAO(VAO.value(), position_index, normal_index, tex_coord_index);
			}
			else {
				model_ptr->setup_VAO(0, position_index, normal_index, tex_coord_index);//Use default VAO object 0
			}

			LOG_INFO(m_logger, "Model successfully loaded from path '" + filename + "'.")
		}
		else {
			std::string errorMsg = "Failed to load model from path '" + filename + "' - ";
			LOG_ERROR(m_logger, errorMsg)
			return nullptr;
		}
		
		return model_ptr;
	}

	std::unique_ptr<Model> ModelFactory::build_model_from_scene(const aiScene& scene)
	{
		Model* model = new Model();
		bool success = init_meshes(scene, *model);

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

	bool ModelFactory::init_meshes(const aiScene& scene, Model& model)
	{
		if (aiNode* root_node = scene.mRootNode; root_node != nullptr) {//if with Initialization since C++17
			process_node(*root_node, scene, model);
			//TODO: Devise method/rules of determining if a model is initialized properly.
			model.m_initialized = true;
			return true;
		}
		return false;
	}

	void ModelFactory::process_node(const aiNode& node, const aiScene& scene, Model& model)
	{
		//process all the node's meshes (if any)
		for (unsigned int mesh_index = 0; mesh_index < node.mNumMeshes; ++mesh_index)
		{
			auto ai_mesh = scene.mMeshes[node.mMeshes[mesh_index]];
			LOG_INFO(m_logger, "MESH NAME: " + std::string(ai_mesh->mName.C_Str()))
			if (auto material_index = ai_mesh->mMaterialIndex; material_index >= 0) {
				aiMaterial* ai_material = scene.mMaterials[material_index];
				aiString str;
				auto texture_count = ai_material->GetTextureCount(aiTextureType::aiTextureType_DIFFUSE);
				for (unsigned int i = 0; i < texture_count; ++i)
				{
					ai_material->GetTexture(aiTextureType::aiTextureType_DIFFUSE, i, &str);
					LOG_INFO(m_logger, "	Texture file located @ '" + std::string(str.C_Str()) + "'")
				}
			}

			model.m_meshes.push_back(generate_rengage_mesh(*ai_mesh));//Copy meshes that make up this parent node.
			model.m_total_vertices += model.m_meshes.back().total_vertices();
			model.m_total_indices += model.m_meshes.back().total_indices();
		}

		//then do the same for each of its children (recursively)
		//this will be useful for retaining the parent-child relation between meshes.
		//TODO: Devise scheme to mark parent and child(ren) meshes during this recursion.
		for (unsigned int child_index = 0; child_index < node.mNumChildren; ++child_index)
		{
			process_node(*(node.mChildren[child_index]), scene, model);
		}
	}

	Mesh ModelFactory::generate_rengage_mesh(const aiMesh& ai_mesh)
	{
		Mesh rengage_mesh{ m_ogl_invoker, m_logger };
		auto vertices = ai_mesh.mVertices;
		auto num_vertices = ai_mesh.mNumVertices;

		//Extract positions, normals, and texture coordinates from aiScene mesh objects
		//then use that info to create RenGage mesh objects
		for (unsigned int vertex_index = 0; vertex_index < num_vertices; ++vertex_index)
		{
			auto current_vertex = vertices[vertex_index];
			Vertex rengage_vertex;

			if (ai_mesh.HasPositions()) {
				rengage_vertex.m_position = { current_vertex.x, current_vertex.y, current_vertex.z };
			}
			else {
				continue;
			}

			if (ai_mesh.HasNormals()) {
				//This is safe because the size of normals array is mNumvertexices in size.
				auto current_normal = ai_mesh.mNormals[vertex_index];
				rengage_vertex.m_normal = { current_normal.x, current_normal.y, current_normal.z };
			}

			if (ai_mesh.HasTextureCoords(0)) {//TODO: Figure out what the texture coordinate set index is.
				//This is safe because the size of texture coordinates array is mNumvertexices in size.
				auto current_uv = ai_mesh.mTextureCoords[0][vertex_index];
				rengage_vertex.m_uv = { current_uv.x, current_uv.y };
			}

			//Add new vertex to mesh's vertex collection.
			rengage_mesh.m_vertices.push_back(rengage_vertex);
		}

		for (unsigned int face_index = 0; face_index < ai_mesh.mNumFaces; ++face_index)
		{
			//A face contains the indices, in correct order, of the vertices we need to draw its primitive.
			auto current_face = ai_mesh.mFaces[face_index];
			for (unsigned int vert_index = 0; vert_index < current_face.mNumIndices; ++vert_index)
			{
				rengage_mesh.m_indices.push_back(current_face.mIndices[vert_index]);
			}
		}
		rengage_mesh.m_initialized = true;
		return rengage_mesh;
	}
}