//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <glm/vec3.hpp> // glm::vec3
//#include <glm/vec4.hpp> // glm::vec4
//#include <glm/mat4x4.hpp> // glm::mat4
//#include <glm/gtc/quaternion.hpp>
//#include <glm/gtx/quaternion.hpp>
//#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
//#include <SOIL2/soil2.h>
//#include <iostream>
//#include <assimp/Importer.hpp>      // C++ importer interface
//#include <assimp/scene.h>           // Output data structure
//#include <assimp/postprocess.h>     // Post processing flags
//
//static bool ImportModelUsingAssimp(const char* pFile) {
//	// Create an instance of the Importer class
//	Assimp::Importer importer;
//
//	// And have it read the given file with some example postprocessing
//	// Usually - if speed is not the most important aspect for you - you'll
//	// probably to request more postprocessing than we do in this example.
//	const aiScene* scene = importer.ReadFile(pFile,
//		aiProcess_CalcTangentSpace |
//		aiProcess_Triangulate |
//		aiProcess_JoinIdenticalVertices |
//		aiProcess_SortByPType);
//	std::cout << "Importing model '" << pFile << "' using Assimp library...\n";
//	// If the import failed, report it
//	if (nullptr == scene) {
//		//DoTheErrorLogging(importer.GetErrorString());
//		std::cout << importer.GetErrorString() << "\n";
//		return false;
//	}
//
//	// Now we can access the file's contents.
//	//DoTheSceneProcessing(scene);
//
//	std::cout << "Filename : " << scene->GetShortFilename(pFile) << "\nMaterials:\n";
//	for (unsigned int i = 0; i < scene->mNumMaterials; ++i)
//	{
//		std::cout << "--Name: " << scene->mMaterials[i]->GetName().C_Str() << "\n";
//	}
//
//	// We're done. Everything will be cleaned up by the importer destructor
//	return true;
//}
//
//int main()
//{
//	if (!ImportModelUsingAssimp("non-existent-file.obj"))
//		std::cout << "ERROR: Failed to load the model file.\n";
//
//
//	GLFWwindow* window;
//
//	/* Initialize the library */
//	if (!glfwInit())
//		return -1;
//
//	/* Create a windowed mode window and its OpenGL context */
//	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//	if (!window)
//	{
//		glfwTerminate();
//		return -1;
//	}
//
//	/* Make the window's context current */
//	glfwMakeContextCurrent(window);
//
//	glfwSwapInterval(1);//Set vsync
//
//	//Must have a valid OpenGL context before initializing glew
//	auto errorCode = glewInit();
//	if (errorCode != GLEW_OK)
//		std::cout << "glewInit() failed with error code (" << errorCode << ")" << std::endl;
//
//
//	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
//
//	/* Loop until the user closes the window */
//	while (!glfwWindowShouldClose(window))
//	{
//		/* Render here */
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		/* Swap front and back buffers */
//		glfwSwapBuffers(window);
//
//		/* Poll for and process events */
//		glfwPollEvents();
//	}
//
//	glfwTerminate();
//
//	return 0;
//}
#include <functional>
#include <iostream>
#include <glm/vec2.hpp>
#include <vector>
#include <rengage.lib/logging/logger_macros.h>
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

template<typename OpenGLFunc, typename ... Args>
void OpenGLCall(OpenGLFunc func, Args&&... args)
{
	//auto current_pid = 123;
	//glGetIntegerv(GL_CURRENT_PROGRAM, &current_pid);
	//LOG_INFO("current_pid = " + std::to_string(current_pid));

	//func(std::forward<Args>(args)...);
	unsigned int errorCount = 0;
	for (GLenum glError = glGetError(); glError != GL_NO_ERROR;) {
		errorCount++;

		//TODO: Need to log more helpful info about error (e.g. function name, which file, line number)
		//std::string caller = __builtin_FUNCTION();
		LOG_ERROR("glErrorCode(" + std::to_string(glError) + ")");// from function \"" + caller + "\"")

		glError = glGetError();
	}

	if (errorCount > 0) {
		std::cout << "Program closed due to OpenGL error(s). Please check log for error code(s).\n";
		exit(0);
	}
}

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
	
	unsigned int VAO = 0; glGenVertexArrays(1, &VAO);

	if (!rengage::model::ModelFactory::load_model("res/models/pine_tree.obj",
												  position_index,
												  normal_index,
												  tex_coord_index,
											      VAO))
	{
		return -1;
	}

	//if (!rengage::model::ModelFactory::load_model("res/models/bat.obj")) {
	//	return -1;
	//}
	//auto current_pid = 123;
	//glGetIntegerv(GL_CURRENT_PROGRAM, &current_pid); glError = glGetError();  std::cout << "glErrorj = " << glError << "\n";
	//LOG_INFO("current_pid = " + std::to_string(current_pid));
	while (!glfwWindowShouldClose(window_ptr))
	{	
		glClear(GL_DEPTH_BUFFER_BIT);
		glClearColor(window_color.r, window_color.g, window_color.b, window_color.a);
		//glClear(GL_COLOR_BUFFER_BIT);
		//OpenGLCall(glClear, GL_DEPTH_BUFFER_BIT);
		//OpenGLCall(glClearColor, window_color.r, window_color.g, window_color.b, window_color.a);
		OpenGLCall(glClear, GL_COLOR_BUFFER_BIT);//1/3/24 current error is coming from gl call(s) during model loading.
		glfwSwapBuffers(window_ptr);
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}