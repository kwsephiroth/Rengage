#pragma once
#include <vector>
#include "vertex.h"

namespace rengage::model {
	class Mesh
	{
	private:
		std::vector<Vertex> m_vertices;

	public:
		Mesh() = default;
		~Mesh() = default;
	};
}