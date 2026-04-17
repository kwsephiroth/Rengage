#include "../rengage.lib/services/ogl_invoker.h"
#include "../rengage.lib/services/service_locator.h"

namespace rengage::services
{
	//namespace
	//{
		void check_for_opengl_error(std::source_location& location)
		{
			unsigned int errorCount = 0;
			for (GLenum glError = glGetError(); glError != GL_NO_ERROR;) {
				errorCount++;
				std::string msg = "glErrorCode(" + std::to_string(glError) + ")";

				auto logger_service_ptr = services::ServiceLocator::get_service<services::logging::ILogger>();
				logger_service_ptr->log(services::logging::LogSeverity::ERROR, msg, location);

				glError = glGetError();
			}

			if (errorCount > 0) {
				std::cout << "Program closed due to OpenGL error(s). Please check log for error code(s).\n";
				exit(0);
			}
		}
	//}
}