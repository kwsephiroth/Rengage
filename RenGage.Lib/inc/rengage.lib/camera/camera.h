#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace rengage::camera
{
	class Camera
	{
	private:
		glm::vec3 m_position;
		glm::vec3 m_right_vector;//U
		glm::vec3 m_up_vector;//V
		glm::vec3 m_forward_vector;//N
		glm::mat4 m_view_matrix;

		bool init();

	public:
		Camera();
		Camera(glm::vec3 init_position);
		~Camera() = default;

		inline glm::vec3 position() const { return m_position; }
		const glm::mat4& view_matrix() const { return m_view_matrix; }

		friend class CameraController;
	};
}

