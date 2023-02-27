#include "../inc/rengage.lib/shader_factory.h"

namespace rengage 
{
	std::unique_ptr<Shader> ShaderFactory::load_shader_from_file(const GLuint type, const std::string& filename)
	{
		std::ifstream input_file;
		std::unique_ptr<Shader> shader_ptr = nullptr;

		input_file.open(filename);
		if (!input_file.good()) {
			LOG_ERROR("Error opening file named '" + std::string {filename} + "'. Please check file or filename.")
			return shader_ptr;
		}

		std::string source;
		std::string line;

		while (!input_file.eof())
		{
			getline(input_file, line);
			source.append(line + "\n");
		}
		input_file.close();

		auto shader_id = glCreateShader(type);
		auto shader_source_ptr = source.c_str();
		auto success = compile_shader_source(shader_id, shader_source_ptr, filename);

		if (success != GL_TRUE) {
			shader_ptr = std::unique_ptr<Shader>(new Shader());
			shader_ptr->m_id = shader_id;
			shader_ptr->m_is_valid = true;
			shader_ptr->m_source = std::move(source);
			shader_ptr->m_type = type;
			shader_ptr->m_file_name = filename;
		}

		return shader_ptr;
	}

	std::unique_ptr<Shader> ShaderFactory::load_shader_from_source(const GLuint type, const std::string& source)
	{
		std::unique_ptr<Shader> shader_ptr = nullptr;
		auto shader_id = glCreateShader(type);
		auto success = compile_shader_source(shader_id, source);

		if (success != GL_TRUE) {
			shader_ptr = std::unique_ptr<Shader>(new Shader());
			shader_ptr->m_id = shader_id;
			shader_ptr->m_is_valid = true;
			shader_ptr->m_source = source;
			shader_ptr->m_type = type;
		}

		return shader_ptr;
	}

	GLint ShaderFactory::compile_shader_source(const GLuint shader_id, const std::string& source, const std::string& filename)
	{
		const char* source_cstr = source.c_str();
		glShaderSource(shader_id, 1, &source_cstr, NULL);
		glCompileShader(shader_id);
		GLint success;
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
		
		if (success != GL_TRUE) {
			GLsizei actual_log_length = 0;
			const unsigned int MAX_LOG_LENGTH = 1024;
			GLchar info_log[MAX_LOG_LENGTH];

			glGetShaderInfoLog(shader_id, MAX_LOG_LENGTH, &actual_log_length, info_log);

			std::stringstream ss;
			ss << "SHADER COMPILATION FAILURE: \n";
			if (!filename.empty()) {
				ss << "Filename: '" << filename << "'\n";
			}
			else {
				ss << "Source: \"" << source << "\"\n";
			}
			ss << "Log: " << info_log << "\n";
			LOG_ERROR(ss.str())
		}

		return success;
	}
}