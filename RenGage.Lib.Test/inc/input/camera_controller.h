#pragma once
#include <rengage.lib/camera/camera.h>
#include "../../inc/interfaces/iobserver.h"
#include <glm/vec3.hpp>

namespace forest_escape::input
{
	using namespace rengage::camera;

	class CameraController : public IObserver
	{
	public:
		CameraController(Camera*);
		void on_notify(EventType, EventArgs) override;

	private:
		Camera* m_camera;
		glm::vec3 m_up_vector;
		glm::vec3 m_right_vector;
		glm::vec3 m_forward_vector;

		void handle_key_press(Key);
		void handle_mouse_movement(Coordinate2D);
		//void translate_camera(glm::vec3 translation);
		//void rotate_camera(float pitch, float yaw);
		void build_view_matrix();
	};
}