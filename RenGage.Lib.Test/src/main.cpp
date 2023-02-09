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

#include <rengage.lib/logger/logger.h>
#include <rengage.lib/rendering_window.h>
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
	int glError = glGetError();
	bool closeProgram = (glError == GL_NO_ERROR) ? false : true;//TODO: Should the program be closed (exception thrown) if even a single error is detected?
	while (glError != GL_NO_ERROR)
	{
		std::cout << glError << '\n';
		glError = glGetError();
	}
	if (closeProgram)
		exit(0);
}

int main()
{
	LOG_INFO("Hello from RenGage.Lib.Test!");
	//rengage::logger::get().log_to_file(rengage::log_severity::INFO, "Hello from RenGage.Lib.Test!");
	rengage::window_attributes window_attribs = {"Test", 1920, 1080};
	auto window = rengage::rendering_window(std::move(window_attribs));
	auto window_color = window.get_color();

	while (!glfwWindowShouldClose(window())) {
		GLCall({ glClear }, GL_DEPTH_BUFFER_BIT);
		GLCall({ glClearColor }, window_color.r, window_color.g, window_color.b, window_color.a);
		GLCall({ glClear }, GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window());
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}