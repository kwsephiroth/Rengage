#pragma once
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <vector>
#include "mesh.h"
#include "../tools/opengl_invoke.h"

namespace rengage::model {
	class Model
	{
	private:
		Model() = default;//TODO: Create public constructor that takes model dependencies as parameters.
		std::vector<Mesh> m_meshes;
		//unsigned int m_num_meshes;
		bool m_initialized = false;
		glm::mat4 m_model_matrix;//Used to transform model coordinates from object to world space.
		GLsizei m_total_vertices = 0;

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
		GLsizei total_vertices() const { return m_total_vertices; }
		GLsizei  total_meshes() const { return m_meshes.size(); }
		const std::vector<Mesh>& meshes() const { return m_meshes; }
	};
};
