#pragma once
#include "shader.h"
#include <fstream>

namespace rengage {
	class ShaderFactory {
	public:
		~ShaderFactory() = default;
		static std::unique_ptr<Shader> get_shader_from_file(const GLuint type, const std::string& filename);
		static std::unique_ptr<Shader> get_shader_from_source(const GLuint type, const std::string& source);

	private:
		ShaderFactory() = default;
	};
}
