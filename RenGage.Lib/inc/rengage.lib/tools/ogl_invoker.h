#pragma once
#include <GL/glew.h>
#include <source_location>
#include <string>
#include <tuple>
#include "../logging/ilogger.h"

namespace rengage
{
#define ARGS(...) std::make_tuple(__VA_ARGS__)

	namespace {
		void check_for_opengl_error(const std::shared_ptr<logging::ILogger>& logger, std::source_location& location)
		{
			unsigned int errorCount = 0;
			for (GLenum glError = glGetError(); glError != GL_NO_ERROR;) {
				errorCount++;
				std::string msg = "glErrorCode(" + std::to_string(glError) + ")";
				logger->log(logging::LogSeverity::ERROR, msg, location);
				glError = glGetError();
			}

			if (errorCount > 0) {
				std::cout << "Program closed due to OpenGL error(s). Please check log for error code(s).\n";
				exit(0);
			}
		}
	}

	class OGLInvoker
	{
	private:
		std::shared_ptr<logging::ILogger> m_logger = nullptr;

	public:
		explicit OGLInvoker(std::shared_ptr<logging::ILogger> logger) :
			m_logger(logger)
		{
		}

		template<typename OpenGLFunc, typename ... Args>
		void invoke(OpenGLFunc func, const std::tuple<Args...>& args_tp, std::source_location location = std::source_location::current())
		{
			std::apply(func, args_tp);
			check_for_opengl_error(m_logger, location);
		}

		template<typename OpenGLFunc>
		void invoke(OpenGLFunc func, std::source_location location = std::source_location::current())
		{
			func();
			check_for_opengl_error(m_logger, location);
		}

		template<typename OpenGLFunc, typename ... Args>
		auto get_invoke(OpenGLFunc func, const std::tuple<Args...>& args_tp, std::source_location location = std::source_location::current())
		{
			auto ret_val = std::apply(func, args_tp);
			check_for_opengl_error(m_logger, location);
			return ret_val;
		}

		template<typename OpenGLFunc>
		auto get_invoke(OpenGLFunc func, std::source_location location = std::source_location::current())
		{
			auto ret_val = func();
			check_for_opengl_error(m_logger, location);
			return ret_val;
		}
	};
}