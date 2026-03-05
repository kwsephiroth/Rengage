#include "../../inc/input/camera_controller.h"
#include <rengage.lib/services/logging/logger_macros.h>
#include <GLFW/glfw3.h>

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
				try
				{
					std::cout << "Translating camera based on key press event." << std::endl;
					auto key = std::any_cast<Key>(event_args);
					handle_key_press(key);
				}
				catch (const std::bad_any_cast& e)
				{
					// Handle the error, e.g., log it or ignore the event
					LOG_ERROR(std::format("Failed to cast event arguments for KeyPressed event: {}", e.what()));
				}
			}
			break;

			case EventType::MouseMoved:
			{
				try
				{
					std::cout << "Rotating camera based on mouse movement event." << std::endl;
					auto coords = std::any_cast<Coordinate2D>(event_args);
					handle_mouse_movement(coords);
				}
				catch (const std::bad_any_cast& e)
				{
					// Handle the error, e.g., log it or ignore the event
					LOG_ERROR(std::format("Failed to cast event arguments for KeyPressed event: {}", e.what()));
				}
			}
			break;
		}
	}

	void CameraController::handle_key_press(Key key)
	{
		// Implement camera movement logic based on the key pressed.
		switch (key)
		{
			case GLFW_KEY_W:
			{
				std::cout << "W key pressed." << std::endl;
			}
			break;

			case GLFW_KEY_A:
			{
				std::cout << "A key pressed." << std::endl;
			}
			break;

			case GLFW_KEY_S:
			{
				std::cout << "S key pressed." << std::endl;
			}
			break;

			case GLFW_KEY_D:
			{
				std::cout << "D key pressed." << std::endl;
			}
			break;
		}
	}

	void CameraController::handle_mouse_movement(Coordinate2D coords)
	{
		// Implement camera rotation logic based on mouse movement.
	}	
}