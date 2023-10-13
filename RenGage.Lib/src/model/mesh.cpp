#include "../../inc/rengage.lib/model/mesh.h"

namespace rengage::model {
	std::ostream& operator<<(std::ostream& os, const Mesh& mesh)
	{
		os << "MESH:\nVertices:\n";
		for (const auto& vertex : mesh.m_vertices)
		{
			os << vertex << "\n\n";
		}
		return os;
	}

	void Mesh::setup_vao()
	{
		//Initialize to dummy values. Will be overwritten with valid ids.
		m_vao = 0;
		m_vbo = 0;
		m_ebo = 0;

		std::cout << "old m_vao = " << m_vao.value() << "\n";
		std::cout << "old m_vbo = " << m_vbo.value() << "\n";
		std::cout << "old m_ebo = " << m_ebo.value() << "\n";
		//Generate buffer/array ids
		glGenVertexArrays(1, &m_vao.value());
		glGenBuffers(1, &m_vbo.value());
		glGenBuffers(1, &m_ebo.value());
		std::cout << "new m_vao = " << m_vao.value() << "\n";
		std::cout << "new m_vbo = " << m_vao.value() << "\n";
		std::cout << "new m_ebo = " << m_ebo.value() << "\n\n";
	}
}