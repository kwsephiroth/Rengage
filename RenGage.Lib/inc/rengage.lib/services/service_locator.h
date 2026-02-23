#pragma once
#include "../interfaces/ilogger.h"
#include "logging/null_logger.h"
#include <unordered_map>
#include <variant>
#include <format>
#include <iostream>
#include <assert.h>

namespace rengage::services
{
	template<typename T>
	concept ServiceType = std::same_as<T, logging::ILogger>;

	using ServiceVariant = std::variant<std::unique_ptr<logging::ILogger>>;
	using TypeHashCode = size_t;

	class ServiceLocator
	{
	public:
		template<ServiceType T>
		static void provide_service(std::unique_ptr<T> service)
		{
			auto& type_id = typeid(T);
			if (!service)
			{
				auto type_name = type_id.name();
				auto error_msg = std::format("Null service '{}' provided.", type_name);
				std::cout << error_msg << std::endl;
				assert(true);
			}
			m_services_map[type_id.hash_code()] = std::move(service);
		}

		template<ServiceType T>
		static T* get_service()
		{
			auto& type_id = typeid(T);
			auto it = m_services_map.find(type_id.hash_code());

			// Check if service has not been provided yet.
			if (it == m_services_map.end())
			{
				auto type_name = type_id.name();
				auto error_msg = std::format("Requested service '{}' has not yet been provided.", type_name);
				std::cout << error_msg << std::endl;
				assert(true);
			}
			
			auto service_ptr = std::get<std::unique_ptr<T>>(it->second).get();
			assert(service_ptr != nullptr);

			// Return reference to service instance.
			return service_ptr;
		}

	private:
		static inline std::unordered_map<TypeHashCode, ServiceVariant> m_services_map;
	};
}