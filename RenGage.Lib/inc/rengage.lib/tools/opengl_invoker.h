#pragma once
#include <GL/glew.h>
#include <source_location>
#include <string>
#include <tuple>
#include "../logging/ilogger.h"

class OpenGLInvoker
{
public:
	template<typename OpenGLFunc, typename ... Args>
	static void invoke(OpenGLFunc func, const std::tuple<Args...>& args_tp, std::source_location location = std::source_location::current())
	{
		std::apply(func, args_tp);
		/*std::apply([&](auto&&... args) {
			func(args...);
			}, args_tp);*/
		check_for_opengl_error(location);
	}

	template<typename OpenGLFunc>
	static void invoke(OpenGLFunc func, std::source_location location = std::source_location::current())
	{
		func();
		check_for_opengl_error(location);
	}

	template<typename OpenGLFunc, typename ... Args>
	static auto get_invoke(OpenGLFunc func, const std::tuple<Args...>& args_tp, std::source_location location = std::source_location::current())
	{
		auto ret_val = std::apply(func, args_tp);
		/*auto ret_val = std::apply([&](auto&&... args)->auto {
			return func(args...);
			}, args_tp);*/
		check_for_opengl_error(location);
		return ret_val;
	}

	template<typename OpenGLFunc>
	static auto get_invoke(OpenGLFunc func, std::source_location location = std::source_location::current())
	{
		auto ret_val = func();
		check_for_opengl_error(location);
		return ret_val;
	}
private:
	static inline std::shared_ptr<rengage::logging::ILogger> m_logger = nullptr;

	static void check_for_opengl_error(std::source_location& location)
	{
		unsigned int errorCount = 0;
		for (GLenum glError = glGetError(); glError != GL_NO_ERROR;) {
			errorCount++;
			std::string msg = "glErrorCode(" + std::to_string(glError) + ")";
			m_logger->log(rengage::logging::LogSeverity::ERROR, msg, location);
			glError = glGetError();
		}

		if (errorCount > 0) {
			std::cout << "Program closed due to OpenGL error(s). Please check log for error code(s).\n";
			exit(0);
		}
	}
};
