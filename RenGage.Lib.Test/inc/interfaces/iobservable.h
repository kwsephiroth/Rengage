#pragma once
#include "iobserver.h"

namespace forest_escape::input
{
	class IObservable
	{
	public:
		virtual ~IObservable() = default;
		virtual void add_observer(IObserver* observer) = 0;
		virtual void remove_observer(IObserver* observer) = 0;
	};
}
