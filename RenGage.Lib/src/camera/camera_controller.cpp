#include "../rengage.lib/camera/camera_controller.h"
#include "services/logging/logger_macros.h"
#include <GLFW/glfw3.h>
#include <glm/gtx/rotate_vector.hpp>

namespace rengage::camera
{
	CameraController::CameraController(Camera* camera) :
		m_camera(camera),
		m_movement_speed(0.1f),
		m_mouse_position({ 0.0f, 0.0f })
	{
	}

	void CameraController::on_notify(EventType event_type, EventArgs event_args)
	{
		switch (event_type)
		{
		case EventType::KeyPressed:
		case EventType::KeyReleased:
			//case EventType::KeyRepeated:
		{
			try
			{
				//std::cout << "Translating camera based on key press event." << std::endl;
				auto key = std::any_cast<Key>(event_args);
				store_key_state(key, event_type);
				//handle_key_press(key);
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
			// Move foward along view direction.
			m_camera->m_eye_position += (m_camera->m_forward_vector * m_movement_speed);
			std::cout << "Camera position after moving forward: " << glm::to_string(m_camera->m_eye_position) << std::endl;
		}
		break;

		case GLFW_KEY_A: // Move left
		{
			//std::cout << "A key pressed." << std::endl;
			//auto left_vector = glm::cross(m_camera->m_forward_vector, m_camera->m_up_vector);
			auto left_vector = glm::cross(m_camera->m_up_vector, m_camera->m_forward_vector);
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
			//auto right_vector = glm::cross(m_camera->m_up_vector, m_camera->m_forward_vector);
			auto right_vector = glm::cross(m_camera->m_forward_vector, m_camera->m_up_vector);
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
		if (m_mouse_position == coords)
			return;

		auto delta_x = 0.0f;
		auto delta_y = 0.0f;

		// TODO: Implement more elegant solution for detecting first look.
		static bool first_look = true;
		if (first_look)
		{
			m_mouse_position = coords;
			first_look = false;
			return;
		}

		if (coords.x != m_mouse_position.x) // x-coordinate changed
		{
			delta_x = (m_mouse_position.x - coords.x) * m_movement_speed;

			// Compute new forward vector (target) by rotation about the up vector (aligned with y-axis initially)
			// TODO: Switch to using quaternions for rotation to avoid gimbal lock and other issues with Euler angles.
			m_camera->m_forward_vector = glm::normalize(glm::rotate(m_camera->m_forward_vector, glm::radians(delta_x), m_camera->m_up_vector));
		}

		//if (coords.y != m_mouse_position.y) // y-coordinate changed
		//{
		//	// TODO: Put limits on this rotation to maintain camera's "up-right" position.
		//	delta_y = (m_mouse_position.y - coords.y) * m_movement_speed;

		//	// TODO: Switch to using quaternions for rotation to avoid gimbal lock and other issues with Euler angles.
		//	auto left_vector = glm::normalize(glm::cross(m_camera->m_forward_vector, m_camera->m_up_vector));
		//	m_camera->m_forward_vector = glm::normalize(glm::rotate(m_camera->m_forward_vector, glm::radians(delta_y), left_vector));
		//	m_camera->m_up_vector = glm::normalize(glm::cross(left_vector, m_camera->m_forward_vector));
		//}

		// Store new mouse position
		m_mouse_position = coords;

		//std::cout << "new mouse position = " << glm::to_string(m_mouse_position) << std::endl;
	}

	void CameraController::store_key_state(Key key, KeyState state)
	{
		switch (key)
		{
		case GLFW_KEY_W:
		case GLFW_KEY_A:
		case GLFW_KEY_S:
		case GLFW_KEY_D:
		case GLFW_KEY_R:
		case GLFW_KEY_F:
			m_key_states[key] = state; // Only store valid keys for camera movement
			break; 
		}
	}

	void CameraController::handle_key_states()
	{
		for (const auto& [key, state] : m_key_states)
		{
			if (state == EventType::KeyPressed)
			{
				handle_key_press(key);
			}
		}
	}
}