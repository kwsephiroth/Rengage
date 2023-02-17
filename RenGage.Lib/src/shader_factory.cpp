#include "../inc/rengage.lib/shader_factory.h"

namespace rengage 
{
	std::unique_ptr<Shader> ShaderFactory::get_shader_from_file(const GLuint type, const std::string& filename)
	{
		return nullptr;
	}

	std::unique_ptr<Shader> ShaderFactory::get_shader_from_source(const GLuint type, const std::string& source)
	{
		return nullptr;
	}
}