#include "../../inc/input/camera_controller.h"

namespace forest_escape::input
{
	CameraController::CameraController(Camera* camera) :
		m_camera(camera)
	{
	}

	void CameraController::on_notify(EventType event_type, EventArgs event_args)
	{
		switch (event_type)
		{
			case EventType::KeyPressed:
			{

			}
			break;

			case EventType::MouseMoved:
			{

			}
			break;
		}
	}
}