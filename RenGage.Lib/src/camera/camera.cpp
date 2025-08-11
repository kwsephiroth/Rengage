#include "../../inc/rengage.lib/camera/camera.h"

namespace rengage::camera
{
	//TODO: Consider using delegating constructor here.
	Camera::Camera()
	{
		init();
	}

	Camera::Camera(glm::vec3 init_position)
		: m_position(init_position)
	{
		init();
	}

	bool Camera::init()
	{
		m_view_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-m_position.x, -m_position.y, -m_position.z));
		return true;
	}
}
