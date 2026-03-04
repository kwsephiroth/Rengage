#pragma once
#include <any>

namespace forest_escape::input
{
	enum class EventType
	{
		KeyPressed,
		KeyReleased,
		MouseMoved,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseScrolled
	};

	using EventArgs = std::any;

	class IObserver
	{
	public:
		virtual ~IObserver() = default;
		virtual void on_notify(EventType, EventArgs) = 0;
	};
}
