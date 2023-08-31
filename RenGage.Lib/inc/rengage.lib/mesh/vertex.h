#pragma once
#include <vector>

namespace rengage {
	struct Vertex
	{
		std::vector<float> m_position;//a 2D or 3D collection of floats - required
		std::vector<float> m_normal;//a 2D or 3D collection of floats - required
		std::vector<float> m_uv;//a 2D collection of floats - texture coordinates are not required

		/*Vertices are "equal" if all their attributes (position, UVs, normals) match*/
		bool operator == (const Vertex& rhs) {
			if (m_position == rhs.m_position &&
				m_normal == rhs.m_normal &&
				m_uv == m_uv) {
				return true;
			}
			return false;
		}
	};
}