#pragma once
#include <vector>
#include <iostream>
#include "vertex.h"

namespace rengage::model {
	class Mesh
	{
	private:		
		Mesh() = default;//TODO: Create public constructor that takes mesh dependencies as parameters.
		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;

	public:
		~Mesh() = default;
		friend class ModelFactory;
		friend std::ostream& operator<<(std::ostream& os, const Mesh& mesh);
	};
}