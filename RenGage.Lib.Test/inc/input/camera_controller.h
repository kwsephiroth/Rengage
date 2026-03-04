#pragma once
#include <rengage.lib/camera/camera.h>
#include "../../inc/interfaces/iobserver.h"
#include "glm/vec2.hpp"

namespace forest_escape::input
{
	using namespace rengage::camera;
	using Key = int;
	using Coordinate2D = glm::vec2;

	class CameraController : public IObserver
	{
	public:
		CameraController(Camera*);
		void on_notify(EventType, EventArgs) override;

	private:
		Camera* m_camera;

		void handle_key_press(Key);
		void handle_mouse_movement(Coordinate2D);
	};
}