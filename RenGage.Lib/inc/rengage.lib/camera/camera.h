#pragma once
#include <glm/vec3.hpp>

namespace rengage::camera
{
	class Camera
	{
	private:
		glm::vec3 m_location = { 0,0,0 };

	public:
		Camera();
		~Camera();

		inline glm::vec3 location() const { return m_location; }
	};
}

