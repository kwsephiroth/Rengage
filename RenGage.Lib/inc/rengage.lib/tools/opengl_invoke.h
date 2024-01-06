#pragma once
#include <GL/glew.h>
#include <source_location>
#include <string>
#include "../logging/logger_macros.h"

namespace {
	void check_for_opengl_error(std::source_location& location)
	{
		unsigned int errorCount = 0;
		for (GLenum glError = glGetError(); glError != GL_NO_ERROR;) {
			errorCount++;
			std::string msg = "glErrorCode(" + std::to_string(glError) + ")";
			Logger::get().log(LogSeverity::ERROR, LogDestination::FILE, msg, location);
			Logger::get().log(LogSeverity::ERROR, LogDestination::CONSOLE, std::move(msg), location);
			glError = glGetError();
		}

		if (errorCount > 0) {
			std::cout << "Program closed due to OpenGL error(s). Please check log for error code(s).\n";
			exit(0);
		}
	}
}
template<typename OpenGLFunc, typename ... Args>
struct opengl_invoke
{
	opengl_invoke(OpenGLFunc func, Args&&... args, std::source_location location = std::source_location::current())
	{
		func(std::forward<Args>(args)...);
		check_for_opengl_error(location);
	}
};

/*template<typename OpenGLFunc, typename ReturnType, typename ... Args>
struct opengl_invoke
{
	opengl_invoke(OpenGLFunc func, ReturnType& destination, Args&&... args, std::source_location location = std::source_location::current())
	{
		destination = func(std::forward<Args>(args)...);
		unsigned int errorCount = 0;
		for (GLenum glError = glGetError(); glError != GL_NO_ERROR;) {
			errorCount++;
			//LOG_ERROR("glErrorCode(" + std::to_string(glError) + ")");
			std::string msg = "glErrorCode(" + std::to_string(glError) + ")";
			Logger::get().log(LogSeverity::ERROR, LogDestination::FILE, std::move(msg), location);
			glError = glGetError();
		}

		if (errorCount > 0) {
			std::cout << "Program closed due to OpenGL error(s). Please check log for error code(s).\n";
			exit(0);
		}
	}
};*/

/*static void opengl_invoke(OpenGLFunc func, Args&&... args)//, std::source_location location = std::source_location::current())
{
	func(std::forward<Args>(args)...);
	unsigned int errorCount = 0;
	for (GLenum glError = glGetError(); glError != GL_NO_ERROR;) {
		errorCount++;
		LOG_ERROR("glErrorCode(" + std::to_string(glError) + ")");
		glError = glGetError();
	}

	if (errorCount > 0) {
		std::cout << "Program closed due to OpenGL error(s). Please check log for error code(s).\n";
		exit(0);
	}
}*/

template<typename OpenGLFunc, typename ... Args>
opengl_invoke(OpenGLFunc func, Args&&... args)->opengl_invoke<OpenGLFunc, Args...>;//User-Defined Deduction Guide since C++20

//template<typename OpenGLFunc, typename ReturnType, typename ... Args>
//opengl_invoke(OpenGLFunc func, ReturnType& destination, Args&&... args)->opengl_invoke<OpenGLFunc, ReturnType, Args...>;