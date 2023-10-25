#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <unordered_map>
#include <iostream>

namespace rengage::model {
	
	enum class VertexAttribType
	{
		POSITION,
		NORMAL,
		TEXCOORD
	};
	
	using VertexAttributeIndex = unsigned int;
	using VertexAttribMap = std::unordered_map<VertexAttribType, VertexAttributeIndex>;

	struct Vertex
	{
		glm::vec3 m_position;//a 3D collection of floats - required
		glm::vec3 m_normal;//a 3D collection of floats - required
		glm::vec2 m_uv = { 0,0 };//a 2D collection of floats - texture coordinates are not required - TODO: Determine if preallocating this is a waste of space.

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

	std::ostream& operator<<(std::ostream& os, const Vertex& vertex);
}