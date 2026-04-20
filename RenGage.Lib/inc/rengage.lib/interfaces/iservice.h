#pragma once

namespace rengage::services
{
	class IService
	{
	protected:
		IService() = default;

	public:
		virtual ~IService() = default;
	};
}