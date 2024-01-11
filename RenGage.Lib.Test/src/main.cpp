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

int main()
{
	LOG_ERROR("Hello from RenGage.Lib.Test!");
	rengage::WindowAttributes window_attribs = { .name="Test", .min_width=1920, .min_height=1080, .color={0.0f, 0.0f, 1.0f, 1.0f}, .swap_interval=1 };//designated initializer since C++20
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
	auto program = rengage::shader::ShaderProgram::create_instance("res/shaders/vertex_shader.glsl",
																   "res/shaders/fragment_shader.glsl");
	if (!program)
	{
		LOG_ERROR("Failed to create shader program. Check logs for error(s).");
		return -1;
	}

	program->use();

	/*If the named attribute variable is not an active attribute in the specified program object
	or if name starts with the reserved prefix "gl_",
	a value of - 1 is returned from glGetAttribLocation.*/
	GLint position_index = opengl_get_invoke(glGetAttribLocation, ARGS(program->id(), "position"));
	GLint normal_index = opengl_get_invoke(glGetAttribLocation, ARGS(program->id(), "normal"));
	GLint tex_coord_index = opengl_get_invoke(glGetAttribLocation, ARGS(program->id(), "tex_coord"));
	
	unsigned int VAO = 0;
	opengl_invoke(glGenVertexArrays, ARGS(1, &VAO));

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
		opengl_invoke(glClear, ARGS(GL_DEPTH_BUFFER_BIT));
		opengl_invoke(glClearColor, ARGS(window_color.r, window_color.g, window_color.b, window_color.a));
		opengl_invoke(glClear, ARGS(GL_COLOR_BUFFER_BIT));
		glfwSwapBuffers(window_ptr);
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}