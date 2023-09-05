#pragma once
#include "shader.h"
#include "../logging/logger_macros.h"
#include <fstream>
#include <sstream>
#include <string>

namespace rengage::shader
{
	class ShaderFactory 
	{
	public:
		~ShaderFactory() = default;
		static std::unique_ptr<Shader> load_shader_from_file(const GLenum type, const std::string& source);
		static std::unique_ptr<Shader> load_shader_from_source(const GLenum type, const std::string& source);

	private:
		ShaderFactory() = default;
		static GLint compile_shader_source(const GLuint shader_id, const std::string& source, const std::string& filename="");
	};
}
