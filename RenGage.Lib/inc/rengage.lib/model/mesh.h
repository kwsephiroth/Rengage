#pragma once
#include <GL/glew.h>
#include <vector>
#include <iostream>
#include <optional>
#include <unordered_map>
#include "vertex.h"
#include "../logging/logger_macros.h"
#include "../tools/opengl_invoke.h"

namespace rengage::model {
	class Mesh
	{
	private:		
		Mesh() = default;//TODO: Create public constructor that takes mesh dependencies as parameters.
		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;
		bool m_initialized = false;

		//IDs are only initialized when mesh is successfully initialized.
		std::optional<GLuint> m_vao = std::nullopt;//vertex attribute object(VAO) id
		std::optional<GLuint> m_vbo = std::nullopt;//vertex buffer object(VBO) id
		std::optional<GLuint> m_ebo = std::nullopt;//element buffer object(EBO) id

		//void setup_VBO(const VertexAttribMap& attribMap);
		void register_VBO(const GLint position_index, const GLint normal_index, const GLint tex_coord_index);
	public:
		~Mesh() = default;
		friend class ModelFactory;
		friend class Model;
		friend std::ostream& operator<<(std::ostream& os, const Mesh& mesh);

		bool initialized() const { return m_initialized; }
		GLsizei total_vertices() const { return m_vertices.size(); }
		const std::vector<unsigned int>& indices () const { return m_indices; }
		std::optional<GLuint> VAO() const { return m_vao; }
		std::optional<GLuint> EBO() const { return m_ebo; }
		std::optional<GLuint> VBO() const { return m_vbo; }
	};
}