#include "../inc/rengage.lib/shader_factory.h"

namespace rengage 
{
	std::unique_ptr<Shader> ShaderFactory::load_shader_from_file(const GLuint type, const char* filename)
	{
		std::ifstream input_file;
		std::unique_ptr<Shader> shader_ptr = nullptr;

		input_file.open(filename);
		if (!input_file.good()) {
			LOG_ERROR("Error opening file named '" + std::string {filename} + "'. Please check file or filename.")
			return shader_ptr;
		}

		std::string shader_source;
		std::string line;

		while (!input_file.eof())
		{
			getline(input_file, line);
			shader_source.append(line + "\n");
		}
		input_file.close();

		auto shader_id = glCreateShader(type);
		auto shader_source_ptr = shader_source.c_str();
		compile_shader_source(shader_id, shader_source_ptr);

		return shader_ptr;
	}

	std::unique_ptr<Shader> ShaderFactory::load_shader_from_source(const GLuint type, const char* source)
	{
		auto shader_id = glCreateShader(type);
		compile_shader_source(shader_id, source);
		return nullptr;
	}

	GLuint ShaderFactory::compile_shader_source(const GLuint shader_id, const char* source)
	{
		glShaderSource(shader_id, 1, &source, NULL);
		glCompileShader(shader_id);
	}
}