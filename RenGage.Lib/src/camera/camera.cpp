#include "../../inc/rengage.lib/camera/camera.h"

namespace rengage::camera
{
	Camera::Camera(glm::vec3 init_position) : 
		m_eye_position(init_position),
		m_up_vector({ 0.0f, 1.0f, 0.0f }),
		m_forward_vector({ 0.0f, 0.0f, -1.0f })
	{
		//init();
	}

	bool Camera::init()
	{
		//m_view_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-m_position.x, -m_position.y, -m_position.z));
		return true;
	}
}
