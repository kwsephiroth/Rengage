#pragma once
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace rengage::camera
{
	class Camera
	{
	private:
		glm::vec3 m_position = { 0,0,1 };
		glm::mat4 m_view_matrix;

		bool init();

	public:
		Camera();
		Camera(glm::vec3 init_position);
		~Camera() = default;

		inline glm::vec3 position() const { return m_position; }
		const glm::mat4& view_matrix() const { return m_view_matrix; }
	};
}

