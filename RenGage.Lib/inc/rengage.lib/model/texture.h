#pragma once
#include <GL/glew.h>
#include <SOIL2/SOIL2.h>
#include <string>
#include "../logging/logger_macros.h"
#include "../tools/ogl_invoker.h"

namespace rengage::model {
	class Texture
	{
	public:
		Texture(const std::string& filename, std::shared_ptr<OGLInvoker> ogl_invoker, std::shared_ptr<ILogger> logger);
		const std::string& filename() const { return m_filename; }
		const GLuint handle() const { return m_handle; } 
		const bool valid() const { return m_valid; }

	private:
		bool load();

		std::string m_filename;
		std::shared_ptr<OGLInvoker> m_ogl_invoker;
		std::shared_ptr<ILogger> m_logger;
		GLuint m_handle;// The Opengl texture handle
		bool m_valid;
	};
}

