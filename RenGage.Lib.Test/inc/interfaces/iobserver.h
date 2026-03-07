#pragma once
#include <any>
#include <glm/glm.hpp>

namespace forest_escape::input
{
	enum class EventType
	{
		Undefined = 0,
		KeyPressed,
		KeyReleased,
		KeyRepeated,
		MouseMoved,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseScrolled
	};

	using EventArgs = std::any;
	using Key = int;
	using Coordinate2D = glm::vec2;

	class IObserver
	{
	public:
		virtual ~IObserver() = default;
		virtual void on_notify(EventType, EventArgs) = 0;
	};
}
