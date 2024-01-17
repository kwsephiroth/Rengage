#pragma once
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace rengage::camera
{
	class Camera
	{
	private:
		glm::vec3 m_location = { 0,0,0 };
		glm::mat4 m_view_matrix;

	public:
		Camera();
		~Camera();

		inline glm::vec3 location() const { return m_location; }
		const glm::mat4& view_matrix() const { return m_view_matrix; }
	};
}

