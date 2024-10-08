#pragma once
#include <GL/glew.h>
#include <memory>
#include "../logging/logger_macros.h"
#include "../logging/file_logger.h"
#include "shader.h"
#include "shader_factory.h"
#include "../tools/ogl_invoker.h"

namespace rengage::shader
{
	class ShaderProgram
	{
	public:
		~ShaderProgram();
		static std::unique_ptr<ShaderProgram> create_instance(const std::string& vertex_shader_path,
															  const std::string& frag_shader_path,
															  std::shared_ptr<OGLInvoker> ogl_invoker,
															  std::shared_ptr<ILogger> logger);

		void attach_shader(GLuint shader_id);
		void use();
		inline GLuint id() const { return m_id; }
		inline bool is_valid() const { return m_is_valid; }

	private:
		ShaderProgram(std::shared_ptr<OGLInvoker> ogl_invoker, std::shared_ptr<ILogger> logger);
		bool link_program();

		GLuint m_id;
		bool m_is_valid = false;
		std::shared_ptr<OGLInvoker> m_ogl_invoker;
		std::shared_ptr<ILogger> m_logger;
	};
}

