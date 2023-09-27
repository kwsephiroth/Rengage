#include "../../inc/rengage.lib/model/mesh.h"

namespace rengage::model {
	std::ostream& operator<<(std::ostream& os, const Mesh& mesh) {
		os << "MESH:\nVertices:\n";
		for (const auto& vertex : mesh.m_vertices) {
			os << vertex << "\n\n";
		}

		return os;
	}
}