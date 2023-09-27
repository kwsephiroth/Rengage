#include "../../inc/rengage.lib/model/vertex.h"

namespace rengage::model {
	std::ostream& operator<<(std::ostream& os, const Vertex& vertex) {
		os << "position: (" << vertex.m_position.x
			<< ", " << vertex.m_position.y
			<< ", " << vertex.m_position.z
			<< ")\nnormal: (" << vertex.m_normal.x
			<< ", " << vertex.m_normal.y
			<< ", " << vertex.m_normal.z
			<< ")\nuv: (" << vertex.m_uv.x
			<< ", " << vertex.m_uv.y << ")";
		return os;
	}
}