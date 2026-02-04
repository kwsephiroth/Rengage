#pragma once
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <vector>
#include "mesh.h"
#include "../tools/ogl_invoker.h"

namespace rengage::model {

	struct ModelParameters
	{
		std::string file_path;
		GLint position_index;
		GLint normal_index;
		GLint tex_coord_index;
		std::optional<GLuint> vao = std::nullopt;
		std::optional<std::string> textures_dir;
		std::optional<std::string> materials_dir;
	};

	using TextureCache = std::unordered_map<std::string, TexturePtr>;

	class Model
	{
	private:
		Model() = default;//TODO: Create public constructor that takes model dependencies as parameters.
		std::vector<Mesh> m_meshes;
		//unsigned int m_num_meshes;
		bool m_initialized = false;
		glm::mat4 m_model_matrix;// Used to transform model coordinates from object to world space.
		size_t m_total_vertices = 0;
		size_t m_total_indices = 0;
		ModelParameters m_params;
		std::shared_ptr<OGLInvoker> m_ogl_invoker;// Used to invoke Open

		//TODO: Refactor the texture cache member to be a service instead.
		inline static TextureCache m_texture_cache; // Cache of loaded textures to avoid redundant texture loading.

		//VAO should be generated ONLY after the model is successfully initialized.
		std::optional<GLuint> m_vao = std::nullopt;//vertex attribute object(VAO) id
		std::optional<GLint> m_position_index = std::nullopt;
		std::optional<GLint> m_normal_index = std::nullopt;
		std::optional<GLint> m_tex_coord_index = std::nullopt;

		void setup_VAO(const GLuint VAO, const GLint position_index, const GLint normal_index, const GLint tex_coord_index);
		void register_VBOs(const GLint position_index, const GLint normal_index, const GLint tex_coord_index);
	public:
		~Model() = default;
		friend class ModelFactory;
		bool initialized() const { return m_initialized; }
		std::optional<GLuint> VAO() { return m_vao; }
		const glm::mat4& model_matrix() const { return m_model_matrix; }
		size_t total_vertices() const { return m_total_vertices; }
		size_t total_indices() const { return m_total_indices; }
		size_t  total_meshes() const { return m_meshes.size(); }
		const std::vector<Mesh>& meshes() const { return m_meshes; }
		const ModelParameters& parameters() const { return m_params; }
	};
}
