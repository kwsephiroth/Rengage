#pragma once
#include <GL/glew.h>
#include <vector>
#include <iostream>
#include <optional>
#include "vertex.h"
#include "../services/logging/logger_macros.h"
#include "../services/service_locator.h"
#include "texture.h"
#include "material.h"

namespace rengage::model {
	using TexturePtr = std::shared_ptr<Texture>;
	using MaterialPtr = std::shared_ptr<Material>;

	class Mesh
	{
	private:
		Mesh() = default;
		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;
		std::vector<TexturePtr> m_textures;
		std::vector<MaterialPtr> m_materials;
		bool m_initialized = false;
		double m_max_depth = 0; 

		//IDs are only initialized when mesh is successfully initialized.
		std::optional<GLuint> m_vao = std::nullopt;//vertex attribute object(VAO) id
		std::optional<GLuint> m_vbo = std::nullopt;//vertex buffer object(VBO) id
		std::optional<GLuint> m_ebo = std::nullopt;//element buffer object(EBO) id

		void register_VBO(const GLuint vao, const GLint position_index, const GLint normal_index, const GLint tex_coord_index);
	public:
		~Mesh() = default;
		friend class ModelFactory;
		friend class Model;
		friend std::ostream& operator<<(std::ostream& os, const Mesh& mesh);

		bool initialized() const { return m_initialized; }
		size_t total_vertices() const { return m_vertices.size(); }
		size_t total_indices() const { return m_indices.size(); }
		const std::vector<unsigned int>& indices() const { return m_indices; }
		std::optional<GLuint> VAO() const { return m_vao; }
		std::optional<GLuint> EBO() const { return m_ebo; }
		std::optional<GLuint> VBO() const { return m_vbo; }
		const std::vector<TexturePtr>& textures() const { return m_textures; }
		const std::vector<MaterialPtr>& materials() const { return m_materials; }
		double max_depth() const { return m_max_depth; }
		void bind() const;
	};
}