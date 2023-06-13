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

#include <rengage.lib/logger/logger_macros.h>
#include <rengage.lib/rendering_window.h>
#include <rengage.lib/shader_factory.h>
#include <functional>
#include <iostream>

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

template<class ReturnType, class... Args>
static void GLCall(std::function<ReturnType(Args&&...)> func, Args&&... args)
{
	func(std::forward<Args>(args)...);
	int glError = glGetError();
	bool closeProgram = (glError == GL_NO_ERROR) ? false : true ;
	while (glError != GL_NO_ERROR)
	{
		std::cout << glError << '\n';
		glError = glGetError();
	}
	if (closeProgram)
		exit(0);

}

template<class... Args>
void GLCall(std::function<void(Args&&...)> func, Args&&... args)
{
	func(std::forward<Args>(args)...);
	unsigned int errorCount = 0;
	for (GLenum glError = glGetError(); glError != GL_NO_ERROR;)
	{
		errorCount++;
		LOG_ERROR("glErrorCode(" + std::to_string(glError) + ")")
		glError = glGetError();
	}

	if (errorCount > 0)
	{
		std::cout << "Program closed due to OpenGL error(s). Please check log for error code(s).\n";
		exit(0);
	}
}

const char* VERTEX_SHADER_SOURCE = 
"#version 430\n\n\
void main(void)\n\
{\n\
	gl_Position = vec4(0.0, 0.0, 0.0, 1.0);\n\
}";

int main()
{
	LOG_ERROR("Hello from RenGage.Lib.Test!");
	rengage::WindowAttributes window_attribs = { "Test", 1920, 1080, {0.0f, 0.0f, 0.0f, 1.0f}, 1 };
	auto window = rengage::RenderingWindow(std::move(window_attribs));
	
	if (!window.initialized()) {
		LOG_ERROR("Rendering window was not properly initialized. Check logs for error(s).")
		return -1;
	}
	//TODO: Maybe setting the OpenGL context and initializing glew SHOULDN'T be the responsibility of a rendering window object.
	auto window_ptr = window.get();
	glfwMakeContextCurrent(window_ptr);
	glfwSwapInterval(window.swap_interval());//Set vsync

	//Must have a valid OpenGL context before initializing glew - TODO: Make sure this happens only once
	auto error_code = glewInit();
	if (error_code != GLEW_OK) {
		LOG_ERROR("Failed to initialize GlEW with error code(" + std::to_string(error_code) + ").");
		return -1;
	}
	LOG_INFO("OpenGL Version: " + std::string((char*)glGetString(GL_VERSION)));

	auto window_color = window.color();
	auto vertex_shader = rengage::ShaderFactory::load_shader_from_source(GL_VERTEX_SHADER, VERTEX_SHADER_SOURCE);//Glew should already be initialized by window construction before this point, else exception will occur
	

	while (!glfwWindowShouldClose(window_ptr)) {
		GLCall({ glClear }, GL_DEPTH_BUFFER_BIT);
		GLCall({ glClearColor }, window_color.r, window_color.g, window_color.b, window_color.a);
		GLCall({ glClear }, GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window_ptr);
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}