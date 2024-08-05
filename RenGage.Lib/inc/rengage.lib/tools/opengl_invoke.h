//#pragma once
//#include <GL/glew.h>
//#include <source_location>
//#include <string>
//#include <tuple>
//#include "../logging/logger_macros.h"
//
//namespace rengage
//{
//#define ARGS(...) std::make_tuple(__VA_ARGS__)
//
//	namespace {
//		void check_for_opengl_error(std::source_location& location)
//		{
//			unsigned int errorCount = 0;
//			for (GLenum glError = glGetError(); glError != GL_NO_ERROR;) {
//				errorCount++;
//				std::string msg = "glErrorCode(" + std::to_string(glError) + ")";
//				Logger::get().log(LogSeverity::ERROR, LogDestination::FILE, msg, location);
//				Logger::get().log(LogSeverity::ERROR, LogDestination::CONSOLE, std::move(msg), location);
//				glError = glGetError();
//			}
//
//			if (errorCount > 0) {
//				std::cout << "Program closed due to OpenGL error(s). Please check log for error code(s).\n";
//				exit(0);
//			}
//		}
//	}
//
//	template<typename OpenGLFunc, typename ... Args>
//	static void opengl_invoke(OpenGLFunc func, const std::tuple<Args...>& args_tp, std::source_location location = std::source_location::current())
//	{
//		std::apply(func, args_tp);
//		/*std::apply([&](auto&&... args) {
//			func(args...);
//			}, args_tp);*/
//		check_for_opengl_error(location);
//	}
//
//	template<typename OpenGLFunc>
//	static void opengl_invoke(OpenGLFunc func, std::source_location location = std::source_location::current())
//	{
//		func();
//		check_for_opengl_error(location);
//	}
//
//	template<typename OpenGLFunc, typename ... Args>
//	static auto opengl_get_invoke(OpenGLFunc func, const std::tuple<Args...>& args_tp, std::source_location location = std::source_location::current())
//	{
//		auto ret_val = std::apply(func, args_tp);
//		/*auto ret_val = std::apply([&](auto&&... args)->auto {
//			return func(args...);
//			}, args_tp);*/
//		check_for_opengl_error(location);
//		return ret_val;
//	}
//
//	template<typename OpenGLFunc>
//	static auto opengl_get_invoke(OpenGLFunc func, std::source_location location = std::source_location::current())
//	{
//		auto ret_val = func();
//		check_for_opengl_error(location);
//		return ret_val;
//	}
//
//	/*template <typename ... Args >
//	static inline auto ARGS(Args&&... args) {//TODO: Consider replacing this with a macro instead.
//		return std::make_tuple(std::forward<Args>(args)...);
//	}*/
//
//	/*struct opengl_invoker
//	{
//		opengl_invoker(std::source_location location = std::source_location::current())
//			: m_src_loc(std::move(location)) {}
//
//		template<typename OpenGLFunc, typename ...Args>
//		void invoke(OpenGLFunc func, Args&&... args)
//		{
//			func(std::forward<Args>(args)...);
//			check_for_opengl_error(m_src_loc);
//		}
//
//		template<typename OpenGLFunc, typename ...Args>
//		auto get_invoke(OpenGLFunc func, Args&&... args)
//			-> decltype(func(std::forward<Args>(args)...))
//		{
//			auto ret_val = func(std::forward<Args>(args)...);
//			check_for_opengl_error(m_src_loc);
//			return ret_val;
//		}
//
//	private:
//		std::source_location m_src_loc;
//	};*/
//
//	/*struct opengl_invoke
//	{
//		opengl_invoke(OpenGLFunc func, Args&&... args, std::source_location location = std::source_location::current())
//		{
//			func(std::forward<Args>(args)...);
//			check_for_opengl_error(location);
//		}
//	};*/
//
//	/*template<typename OpenGLFunc, typename ReturnType, typename ... Args>
//	struct opengl_invoke
//	{
//		opengl_invoke(OpenGLFunc func, ReturnType& destination, Args&&... args, std::source_location location = std::source_location::current())
//		{
//			destination = func(std::forward<Args>(args)...);
//			unsigned int errorCount = 0;
//			for (GLenum glError = glGetError(); glError != GL_NO_ERROR;) {
//				errorCount++;
//				//LOG_ERROR("glErrorCode(" + std::to_string(glError) + ")");
//				std::string msg = "glErrorCode(" + std::to_string(glError) + ")";
//				Logger::get().log(LogSeverity::ERROR, LogDestination::FILE, std::move(msg), location);
//				glError = glGetError();
//			}
//
//			if (errorCount > 0) {
//				std::cout << "Program closed due to OpenGL error(s). Please check log for error code(s).\n";
//				exit(0);
//			}
//		}
//	};*/
//
//	/*static void opengl_invoke(OpenGLFunc func, Args&&... args)//, std::source_location location = std::source_location::current())
//	{
//		func(std::forward<Args>(args)...);
//		unsigned int errorCount = 0;
//		for (GLenum glError = glGetError(); glError != GL_NO_ERROR;) {
//			errorCount++;
//			LOG_ERROR("glErrorCode(" + std::to_string(glError) + ")");
//			glError = glGetError();
//		}
//
//		if (errorCount > 0) {
//			std::cout << "Program closed due to OpenGL error(s). Please check log for error code(s).\n";
//			exit(0);
//		}
//	}*/
//
//	//template<typename OpenGLFunc, typename ... Args>
//	//opengl_invoke(OpenGLFunc func, Args&&... args)->opengl_invoke<OpenGLFunc, Args...>;//User-Defined Deduction Guide since C++17
//
//	//template<typename OpenGLFunc, typename ReturnType, typename ... Args>
//	//opengl_invoke(OpenGLFunc func, ReturnType& destination, Args&&... args)->opengl_invoke<OpenGLFunc, ReturnType, Args...>;
//}