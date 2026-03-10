#pragma once
#include "iobserver.h"

namespace rengage
{
	class IObservable
	{
	public:
		virtual ~IObservable() = default;
		virtual void add_observer(IObserver* observer) = 0;
		virtual void remove_observer(IObserver* observer) = 0;
	};
}
