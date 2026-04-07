#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>

namespace rengage::camera
{
	class Camera
	{
	private:
		glm::vec3 m_eye_position;
		//glm::vec3 m_right_vector;//U
		glm::vec3 m_up_vector;//V
		glm::vec3 m_forward_vector;//N - the "target" to look at
		//glm::mat4 m_view_matrix;
		glm::quat m_orientation; // Current camera orientation

		bool init();

	public:
		//Camera();
		Camera(glm::vec3 init_position = { 0.0f, 0.0f, 1.0f });
		~Camera() = default;

		inline glm::vec3 position() const { return m_eye_position; }
		//const glm::mat4& view_matrix() const { return m_view_matrix; }
		glm::mat4 view_matrix() const 
		{
			//glm::mat4 view_matrix = glm::mat4(1.0f);
			//glm::vec3 N = glm::normalize(m_forward_vector);
			//glm::vec3 U = glm::normalize(glm::cross(m_up_vector, N));
			//glm::vec3 V = glm::cross(N, U);
			//
			//view_matrix[0][0] = U.x;  view_matrix[0][1] = U.y;  view_matrix[0][2] = U.z;  view_matrix[0][3] = -m_position.x;
			//view_matrix[1][0] = V.x;  view_matrix[1][1] = V.y;  view_matrix[1][2] = V.z;  view_matrix[1][3] = -m_position.y;
			//view_matrix[2][0] = N.x;  view_matrix[2][1] = N.y;  view_matrix[2][2] = N.z;  view_matrix[2][3] = -m_position.z;
			//view_matrix[3][0] = 0.0f; view_matrix[3][1] = 0.0f; view_matrix[3][2] = 0.0f; view_matrix[3][3] = 1.0f;

			auto view_matrix = glm::lookAt(m_eye_position, m_eye_position + m_forward_vector, m_up_vector);
			//static bool printed;
			//if (!printed)
			//{
			//	std::cout << glm::to_string(view_matrix) << "\n";
			//	printed = true;
			//}
			return view_matrix;
		}

		friend class CameraController;
	};
}

