#pragma once
#include "shader.h"
#include "../logging/logger_macros.h"
#include "../tools/ogl_invoker.h"
#include <fstream>
#include <sstream>
#include <string>

namespace rengage::shader
{
	class ShaderFactory 
	{
	public:
		ShaderFactory(std::shared_ptr<OGLInvoker> oglInvoker, std::shared_ptr<ILogger> logger) :
			m_ogl_invoker(std::move(oglInvoker)),
			m_logger(std::move(logger)) {}
		~ShaderFactory() {}
		std::unique_ptr<Shader> load_shader_from_file(const GLenum type, const std::string& filename);
		std::unique_ptr<Shader> load_shader_from_source(const GLenum type, const std::string& source);

	private:
		std::shared_ptr<OGLInvoker> m_ogl_invoker;
		std::shared_ptr<ILogger> m_logger;
		GLint compile_shader_source(const GLuint shader_id, const std::string& source, const std::string& filename="");
	};
}
