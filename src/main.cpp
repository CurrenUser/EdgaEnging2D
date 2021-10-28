#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void WindowResize(GLFWwindow* window, int width, int height);

int main() {

// main window setings
GLFWwindow* window = nullptr;
unsigned int window_width = 800;
unsigned int window_height = 600;
const char* window_name = "EdgaEngine2D";


const char** glfw_error = nullptr;

  if ( !glfwInit() ) { // initialization glfw
	glfwGetError(glfw_error);
	std::cout << "Can`t initialization GLFW, error:" << glfw_error << "\n";
	return -1;
  }
  
  // seting opengl contexts
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // creating main window
  window = glfwCreateWindow(window_width, window_height, window_name, NULL, NULL);
  if (!window) {
	glfwGetError(glfw_error);
	std::cout << "Can`t initialization window, error:" << glfw_error << "\n";
	glfwTerminate();
	return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // initialization glad
	  std::cout << "Cat`t initialization GLAD \n";
	  return -1;
  }

  glViewport(0, 0, window_width, window_height); // domain of viewer
  glfwSetFramebufferSizeCallback(window,WindowResize); // callback for resize window
  
  while (!glfwWindowShouldClose(window)) { // loop of render


	  glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	  glClear(GL_COLOR_BUFFER_BIT);

	  glfwSwapBuffers(window);
	  glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

void WindowResize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}