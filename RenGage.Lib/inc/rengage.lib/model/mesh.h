#pragma once
#include <GL/glew.h>
#include <vector>
#include <iostream>
#include <optional>
#include "vertex.h"

namespace rengage::model {
	class Mesh
	{
	private:		
		Mesh() = default;//TODO: Create public constructor that takes mesh dependencies as parameters.
		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;

		//IDs are only initialized when mesh is successfully initialized.
		std::optional<unsigned int> m_vao = std::nullopt;//vertex attribute object(VAO) id
		std::optional<unsigned int> m_vbo = std::nullopt;//vertex buffer object(VBO) id
		std::optional<unsigned int> m_ebo = std::nullopt;//element buffer object(EBO) id

		void setup_vao();

	public:
		~Mesh() = default;
		friend class ModelFactory;
		friend std::ostream& operator<<(std::ostream& os, const Mesh& mesh);
		std::optional<unsigned int> VAO() { return m_vao; }
	};
}