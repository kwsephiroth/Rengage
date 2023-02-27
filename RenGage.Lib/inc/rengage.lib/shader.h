#pragma once
#include <GL/glew.h>
#include <string>

namespace rengage 
{
	struct ShaderFileInfo
	{
		GLenum type;
		std::string file_name;
	};

	class Shader 
	{
	public:
		~Shader() = default;
		inline GLuint id() const { return m_id; }
		inline GLenum type() const { return m_type; }
		inline bool is_valid() const { return m_is_valid; }
		inline std::string source() const { return m_source; }
		inline std::string file_name() const { return m_file_name; }
		friend class ShaderFactory;

	private:		
		Shader() = default;
		bool m_is_valid = false;
		GLuint m_id;
		GLenum m_type;
		std::string m_file_name;
		std::string m_source;
	};
}
