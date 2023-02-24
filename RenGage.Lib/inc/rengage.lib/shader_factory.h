#pragma once
#include "shader.h"
#include "logger/logger_macros.h"
#include <fstream>

namespace rengage {
	class ShaderFactory {
	public:
		~ShaderFactory() = default;
		static std::unique_ptr<Shader> load_shader_from_file(const GLuint type, const char* source);
		static std::unique_ptr<Shader> load_shader_from_source(const GLuint type, const char* source);

	private:
		ShaderFactory() = default;
		static GLuint compile_shader_source(const GLuint shader_id, const char* source);
	};
}
