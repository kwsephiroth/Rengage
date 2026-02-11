#pragma once
#include "logging/ilogger.h"
#include "logging/null_logger.h"
#include <unordered_map>
#include <variant>

namespace rengage::services
{
	template<typename T>
	concept ServiceType = std::same_as<T, logging::ILogger>;

	using ServiceVariant = std::variant<std::shared_ptr<logging::ILogger>>;
	using TypeHashCode = size_t;

	class ServiceLocator
	{
	public:
		template<ServiceType T>
		static void provide_service(std::shared_ptr<T> service)
		{
			assert(service != nullptr && "Null service provided.");
			m_services_map[typeid(T).hash_code()] = service;
		}

		template<ServiceType T>
		static const T& get_service()
		{
			auto it = m_services_map.find(typeid(T).hash_code());

			// Check if service has not been provided yet.
			assert(it != m_services_map.end() && "Requested service has not yet been provided.");
			auto service_ptr = std::get<std::shared_ptr<T>>(it->second);
			assert(service_ptr != nullptr);

			// Return reference to service instance.
			return  *service_ptr;
		}

	private:
		static inline std::unordered_map<TypeHashCode, ServiceVariant> m_services_map;
	};
}