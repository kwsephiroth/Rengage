#pragma once
#include <GL/glew.h>
#include <vector>
#include <iostream>
#include <optional>
#include "vertex.h"
#include "../logging/logger_macros.h"
#include "../tools/ogl_invoker.h"
#include "texture.h"

namespace rengage::model {
	using TexturePtr = std::shared_ptr<Texture>;

	class Mesh
	{
	private:
		Mesh(std::shared_ptr<OGLInvoker> ogl_invoker, std::shared_ptr<ILogger> logger) :
			m_ogl_invoker(std::move(ogl_invoker)),
			m_logger(std::move(logger))
		{}

		std::shared_ptr<OGLInvoker> m_ogl_invoker;
		std::shared_ptr<ILogger> m_logger;
		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;
		std::vector<TexturePtr> m_textures;
		bool m_initialized = false;

		//IDs are only initialized when mesh is successfully initialized.
		std::optional<GLuint> m_vao = std::nullopt;//vertex attribute object(VAO) id
		std::optional<GLuint> m_vbo = std::nullopt;//vertex buffer object(VBO) id
		std::optional<GLuint> m_ebo = std::nullopt;//element buffer object(EBO) id

		void register_VBO(const GLint position_index, const GLint normal_index, const GLint tex_coord_index);
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
	};
}