#pragma once
#include "camera.h"
#include "../interfaces/iobserver.h"
#include <glm/glm.hpp>
#include <map>

namespace rengage::camera
{
	using KeyState = EventType;
	class CameraController : public IObserver
	{
	public:
		CameraController(Camera*);
		void on_notify(EventType, EventArgs) override;
		void set_movement_speed(float movement_speed);
		inline float movement_speed() const { return m_movement_speed; }
		void process_key_input();

	private:
		Camera* m_camera;
		float m_movement_speed;
		glm::vec2 m_mouse_position;
		//std::map<Key, KeyState> m_key_states; // Map to track the state of keys (pressed, released)

		void handle_key_press(Key);
		void handle_mouse_movement(Coordinate2D);
		//void store_key_state(Key, KeyState);
		//void translate_camera(glm::vec3 translation);
		//void rotate_camera(float pitch, float yaw);
		//void build_view_matrix();
	};
}