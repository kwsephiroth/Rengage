#pragma once
#include "shader.h"
#include <fstream>
#include <sstream>
#include <string>
#include "../services/logging/logger_macros.h"

namespace rengage::shader
{
	class ShaderFactory
	{
	public:
		ShaderFactory() = default;
		~ShaderFactory() {}
		std::unique_ptr<Shader> load_shader_from_file(const GLenum type, const std::string& filename);
		std::unique_ptr<Shader> load_shader_from_source(const GLenum type, const std::string& source);

	private:
		std::shared_ptr<services::logging::ILogger> m_logger;
		GLint compile_shader_source(const GLuint shader_id, const std::string& source, const std::string& filename = "");
	};
}
