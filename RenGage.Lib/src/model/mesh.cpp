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

	//void Mesh::setup_VBO(const VertexAttribMap& attribMap)//TODO: This might need to be done once at the Model-level since all buffer data has the same format.
	//{
	//	//First make sure map has valid attributes.
	//	if (attribMap.empty() || attribMap.size() < 3) {
	//		//TODO: Log error then return
	//		return;
	//	}

	//	auto position_itr = attribMap.find(VertexAttribType::POSITION);
	//	if (position_itr == attribMap.end()) {
	//		//TODO: Log error then return
	//		return;
	//	}
	//	auto normal_itr = attribMap.find(VertexAttribType::NORMAL);
	//	if (normal_itr == attribMap.end()) {
	//		//TODO: Log error then return
	//		return;
	//	}
	//	auto texcoord_itr = attribMap.find(VertexAttribType::TEXCOORD);
	//	if (texcoord_itr == attribMap.end()) {
	//		//TODO: Log error then return
	//		return;
	//	}

	//	VertexAttributeIndex position_attrib_index = position_itr->second;
	//	VertexAttributeIndex normal_attrib_index = normal_itr->second;
	//	VertexAttributeIndex texcoord_attrib_index = texcoord_itr->second;

	//	//TODO: VAO needs to be bound first
	//	////Initialize to dummy values. Will be overwritten with valid ids.
	//	m_vbo = 0;
	//	//m_ebo = 0;

	//	std::cout << "old m_vbo = " << m_vbo.value() << "\n";
	//	//std::cout << "old m_ebo = " << m_ebo.value() << "\n";
	//	////Generate buffer/array ids
	//	glGenBuffers(1, &m_vbo.value());
	//	//glGenBuffers(1, &m_ebo.value());

	//	std::cout << "new m_vbo = " << m_vbo.value() << "\n";
	//	//std::cout << "new m_ebo = " << m_ebo.value() << "\n\n";

	//	glBindBuffer(GL_ARRAY_BUFFER, m_vbo.value());
	//	glBufferData(GL_ARRAY_BUFFER, size(m_vertices), &m_vertices[0], GL_STATIC_DRAW);
	//	
	//	size_t vertex_stride = sizeof(Vertex);
	//	GLintptr vertex_position_offset = 0 * sizeof(float);
	//	GLintptr vertex_normal_offset = 3 * sizeof(float);
	//	GLintptr vertex_texcoord_offset = 6 * sizeof(float);

	//	//setup position attribute
	//	glEnableVertexAttribArray(position_attrib_index);
	//	glVertexAttribPointer(position_attrib_index, 3, GL_FLOAT, false, vertex_stride, (GLvoid*)vertex_position_offset);

	//	//setup normal attribute
	//	glEnableVertexAttribArray(normal_attrib_index);
	//	glVertexAttribPointer(normal_attrib_index, 3, GL_FLOAT, false, vertex_stride, (GLvoid*)vertex_normal_offset);

	//	//setup uv(texture coordinate) attribute
	//	glEnableVertexAttribArray(texcoord_attrib_index);
	//	glVertexAttribPointer(texcoord_attrib_index, 3, GL_FLOAT, false, vertex_stride, (GLvoid*)vertex_texcoord_offset);

	//	//TODO: Unbind VAO
	//	//TODO: Unbind VBOS
	//}

	void Mesh::register_VBO(const unsigned int position_index, const unsigned int normal_index, const unsigned int tex_coord_index)
	{
		if (m_vertices.empty()) {
			//Log error and return
			LOG_ERROR("Mesh has no vertices.");
			return;
		}
		//TODO: VAO needs to be bound first
		////Initialize to dummy values. Will be overwritten with valid ids.
		m_vbo = 0;
		m_ebo = 0;

		//std::cout << "old m_vbo = " << m_vbo.value() << "\n";
		//std::cout << "old m_ebo = " << m_ebo.value() << "\n";
		////Generate buffer/array ids
		glGenBuffers(1, &m_vbo.value());
		glGenBuffers(1, &m_ebo.value());

		//std::cout << "new m_vbo = " << m_vbo.value() << "\n";
		//std::cout << "new m_ebo = " << m_ebo.value() << "\n\n";
		//Point VBO at vertex data
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo.value());
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);
		
		//Point EBO at face indices
		glBindBuffer(GL_ARRAY_BUFFER, m_ebo.value());
		glBufferData(GL_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

		size_t vertex_stride = sizeof(Vertex);
		GLintptr vertex_position_offset = 0 * sizeof(float);
		GLintptr vertex_normal_offset = 3 * sizeof(float);
		GLintptr vertex_texcoord_offset = 6 * sizeof(float);

		//setup position attribute
		glEnableVertexAttribArray(position_index);
		glVertexAttribPointer(position_index, 3, GL_FLOAT, false, vertex_stride, (GLvoid*)vertex_position_offset);

		//setup normal attribute
		glEnableVertexAttribArray(normal_index);
		glVertexAttribPointer(normal_index, 3, GL_FLOAT, false, vertex_stride, (GLvoid*)vertex_normal_offset);

		//setup uv(texture coordinate) attribute
		glEnableVertexAttribArray(tex_coord_index);
		glVertexAttribPointer(tex_coord_index, 3, GL_FLOAT, false, vertex_stride, (GLvoid*)vertex_texcoord_offset);
	}
}