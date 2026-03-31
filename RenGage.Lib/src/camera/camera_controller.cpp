#include "../rengage.lib/camera/camera_controller.h"
#include "services/logging/logger_macros.h"
#include <GLFW/glfw3.h>

namespace rengage::camera
{
	CameraController::CameraController(Camera* camera) :
		m_camera(camera),
		m_movement_speed(0.5f),
		m_mouse_position({ 0.0f, 0.0f })
	{
	}

	void CameraController::on_notify(EventType event_type, EventArgs event_args)
	{
		switch (event_type)
		{
		case EventType::KeyPressed:
		case EventType::KeyRepeated:
		{
			try
			{
				//std::cout << "Translating camera based on key press event." << std::endl;
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
				//std::cout << "Rotating camera based on mouse movement event." << std::endl;
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

	void CameraController::set_movement_speed(float movement_speed)
	{
		m_movement_speed = movement_speed;
	}

	void CameraController::handle_key_press(Key key)
	{
		// Implement camera movement logic based on the key pressed.
		switch (key)
		{
		case GLFW_KEY_W: // Move forward
		{
			//std::cout << "W key pressed." << std::endl;
			m_camera->m_eye_position += (m_camera->m_forward_vector * m_movement_speed);
			std::cout << "Camera position after moving forward: " << glm::to_string(m_camera->m_eye_position) << std::endl;
		}
		break;

		case GLFW_KEY_A: // Move left
		{
			//std::cout << "A key pressed." << std::endl;
			auto left_vector = glm::cross(m_camera->m_forward_vector, m_camera->m_up_vector);
			left_vector = glm::normalize(left_vector);
			m_camera->m_eye_position += (left_vector * m_movement_speed);
			std::cout << "Camera position after moving left: " << glm::to_string(m_camera->m_eye_position) << std::endl;
		}
		break;

		case GLFW_KEY_S: // Move backward
		{
			//std::cout << "S key pressed." << std::endl;
			m_camera->m_eye_position -= (m_camera->m_forward_vector * m_movement_speed);
			std::cout << "Camera position after moving backward: " << glm::to_string(m_camera->m_eye_position) << std::endl;
		}
		break;

		case GLFW_KEY_D: // Move right
		{
			//std::cout << "D key pressed." << std::endl;
			auto right_vector = glm::cross(m_camera->m_up_vector, m_camera->m_forward_vector);
			right_vector = glm::normalize(right_vector);
			m_camera->m_eye_position += (right_vector * m_movement_speed);
			std::cout << "Camera position after moving right: " << glm::to_string(m_camera->m_eye_position) << std::endl;
		}
		break;

		case GLFW_KEY_R: // Raise the camera up
		{
			m_camera->m_eye_position.y += m_movement_speed;
			std::cout << "Camera position after moving up: " << glm::to_string(m_camera->m_eye_position) << std::endl;
		}
		break;

		case GLFW_KEY_F: // Lower the camera down
		{
			m_camera->m_eye_position.y -= m_movement_speed;
			std::cout << "Camera position after moving down: " << glm::to_string(m_camera->m_eye_position) << std::endl;
		}
		break;
		}
	}

	void CameraController::handle_mouse_movement(Coordinate2D coords) // Receives 2D Screen Coordinates
	{
		// Implement camera rotation logic based on mouse movement.
		// TODO: Compare new mouse position to previous mouse position.
		auto delta_x = 0.0f;
		auto delta_y = 0.0f;

		if (coords.x != m_mouse_position.x) // x-coordinate changed
		{
			delta_x = m_mouse_position.x - coords.x;

			//if (coords.x > m_mouse_position.x)
			if (delta_x < 0)
			{
				std::cout << "Rotating camera to the right..." << std::endl;
			}
			else
			{
				std::cout << "Rotation camera to the left..." << std::endl;
			}
		}

		if (coords.y != m_mouse_position.y) // y-coordinate changed
		{
			delta_y = m_mouse_position.y - coords.y;

			//if (coords.y < m_mouse_position.y) // Y-value increases downward in 2D Screen Coordinates
			if (delta_y > 0)
			{
				std::cout << "Rotating camera up..." << std::endl;
			}
			else
			{
				std::cout << "Rotation camera down..." << std::endl;
			}
		}

		// Store new mouse position
		m_mouse_position = coords;
	}
}