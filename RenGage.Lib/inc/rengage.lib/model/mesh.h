#pragma once
#include <vector>
#include <iostream>
#include "vertex.h"

namespace rengage::model {
	class Mesh
	{
	private:		
		Mesh() = default;
		std::vector<Vertex> m_vertices;

		//Temporary buffers. TODO: Consider moving these into the ModelFactory load process.
		std::vector<glm::vec3> m_positions;
		std::vector<glm::vec3> m_normals;
		std::vector<glm::vec2> m_uvs;

	public:
		~Mesh() = default;
		friend class ModelFactory;
		friend std::ostream& operator<<(std::ostream& os, const Mesh& mesh);
	};
}