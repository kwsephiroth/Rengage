#pragma once
#include <GL/glew.h>
#include <source_location>
#include <string>
#include <tuple>
#include "../interfaces/ilogger.h"
#include "../interfaces/iservice.h"
//#include "../services/service_locator.h"

namespace rengage::services
{
#define ARGS(...) std::make_tuple(__VA_ARGS__)

	//namespace {
		//void check_for_opengl_error(std::source_location& location);
	//}

	extern void check_for_opengl_error(std::source_location& location);

	class OGLInvoker final : public IService
	{
	public:
		OGLInvoker() = default;

		template<typename OpenGLFunc, typename ... Args>
		void invoke(OpenGLFunc func, const std::tuple<Args...>& args_tp, std::source_location location = std::source_location::current())
		{
			std::apply(func, args_tp);
			check_for_opengl_error(location);
		}

		template<typename OpenGLFunc>
		void invoke(OpenGLFunc func, std::source_location location = std::source_location::current())
		{
			func();
			check_for_opengl_error(location);
		}

		template<typename OpenGLFunc, typename ... Args>
		auto get_invoke(OpenGLFunc func, const std::tuple<Args...>& args_tp, std::source_location location = std::source_location::current())
		{
			auto ret_val = std::apply(func, args_tp);
			check_for_opengl_error(location);
			return ret_val;
		}

		template<typename OpenGLFunc>
		auto get_invoke(OpenGLFunc func, std::source_location location = std::source_location::current())
		{
			auto ret_val = func();
			check_for_opengl_error(location);
			return ret_val;
		}
	};
}