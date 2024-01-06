#include <functional>
#include <iostream>
#include <glm/vec2.hpp>
#include <vector>
#include <rengage.lib/logging/logger_macros.h>
#include <rengage.lib/tools/opengl_invoke.h>
#include <rengage.lib/rendering_window.h>
#include <rengage.lib/shader/shader_factory.h>
#include <rengage.lib/shader/shader_program.h>
#include <rengage.lib/model/model_factory.h>
#include <rengage.lib/model/vertex.h>

enum class ErrorCode
{
	FAIL=0,
	SUCCESS=1
};

struct GLResult
{
	ErrorCode error_code = ErrorCode::FAIL;
	std::string error_msg;
};

#define GLCALL(function, ...) \
	function(__VA_ARGS__);	  \
	std::cout << "GLCALL invoked!\n"; \

const char* VERTEX_SHADER_SOURCE = 
"#version 460\n\n\
void main(void)\n\
{\n\
	gl_Position = vec4(0.0, 0.0, 0.0, 1.0);\n\
}";

int main()
{
	LOG_ERROR("Hello from RenGage.Lib.Test!");
	rengage::WindowAttributes window_attribs = { .name="Test", .min_width=1920, .min_height=1080, .color={0.0f, 0.0f, 0.0f, 1.0f}, .swap_interval=1 };//designated initializer since C++20
	auto window = rengage::RenderingWindow(std::move(window_attribs));//copy or move constructor invoked here.
	
	if (!window.initialized()) {
		LOG_ERROR("Rendering window was not properly initialized. Check logs for error(s).")
		return -1;
	}
	//TODO: Maybe setting the OpenGL context and initializing glew SHOULDN'T be the responsibility of a rendering window object.
	auto window_ptr = window.get();
	glfwMakeContextCurrent(window_ptr);
	glfwSwapInterval(window.swap_interval());//Set vsync

	//Must have a valid OpenGL context before initializing glew - TODO: Make sure this happens only once
	auto error_code = glewInit();//Glew must initialized in order to make OpenGL function calls.
	if (error_code != GLEW_OK) {
		LOG_ERROR("Failed to initialize GLEW with error code(" + std::to_string(error_code) + ").");
		return -1;
	}
	LOG_INFO("OpenGL Version: " + std::string((char*)glGetString(GL_VERSION)));

	auto window_color = window.color();
	//auto vertex_shader = rengage::shader::ShaderFactory::load_shader_from_source(GL_VERTEX_SHADER, VERTEX_SHADER_SOURCE);//Glew should already be initialized by window construction before this point, else exception will occur
	//auto vertex_shader = rengage::shader::ShaderFactory::load_shader_from_file(GL_VERTEX_SHADER, "res/shaders/vertex_shader.glsl");
	//auto frag_shader = rengage::shader::ShaderFactory::load_shader_from_file(GL_FRAGMENT_SHADER, "res/shaders/fragment_shader.glsl");
	//
	//if (vertex_shader == nullptr || frag_shader == nullptr || !vertex_shader->is_valid() || !frag_shader->is_valid()) {
	//	LOG_ERROR("Failed to load shader(s). Check logs for error(s).");
	//	return -1;
	//}

	//TODO: Attach shaders to shader program here
	auto program = rengage::shader::ShaderProgram::create_instance("res/shaders/vertex_shader.glsl",
																   "res/shaders/fragment_shader.glsl");
	if (!program)
	{
		LOG_ERROR("Failed to create shader program. Check logs for error(s).");
		return -1;
	}

	program->use();
	rengage::model::VertexAttributeIndex position_index = glGetAttribLocation(program->id(), "position");
	rengage::model::VertexAttributeIndex normal_index = glGetAttribLocation(program->id(), "normal");
	rengage::model::VertexAttributeIndex tex_coord_index = glGetAttribLocation(program->id(), "tex_coord");
	
	unsigned int VAO = 0;
	opengl_invoke(glGenVertexArrays, 1, &VAO);

	if (!rengage::model::ModelFactory::load_model("res/models/pine_tree.obj",
												  position_index,
												  normal_index,
												  tex_coord_index,
											      VAO))
	{
		return -1;
	}

	while (!glfwWindowShouldClose(window_ptr))
	{	
		opengl_invoke(glClear, GL_DEPTH_BUFFER_BIT);
		opengl_invoke(glClearColor, window_color.r, window_color.g, window_color.b, window_color.a);
		opengl_invoke(glClear, GL_COLOR_BUFFER_BIT);//1/3/24 current error is coming from gl call(s) during model loading.
		glfwSwapBuffers(window_ptr);
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}