#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shaders.h"
#include <iostream>
#include <vector>



void WindowResize(GLFWwindow* window, int width, int height);
void KeyInput(GLFWwindow* window, int key, int scancode, int action, int modes);

int main() {

Shaders shaders; // shader class

std::vector<float> trangle_vertices1 = {
	-0.5f,  0.5f, 0.0f,
	-0.8f, -0.2f, 0.0f,
	-0.2f, -0.2f, 0.0f
	-0.2f,  0.0f, 0.0f
};

std::vector<unsigned int> indices = { 0,1,2, 3,0,2 };

std::vector<unsigned int> indices2 = { 0,1,2 };

std::vector<float> trangle_vertices2 = {
	0.5f, 0.5f, 0.0f,
	0.8f, -0.2f, 0.0f,
	0.2f, -0.2f, 0.0f
};

// main window setings
GLFWwindow* window = nullptr;
unsigned int window_width = 1024;
unsigned int window_height = 800;
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
  glfwSetKeyCallback(window, KeyInput); // callback for keyboard

  GLuint VAO1 = 0, VBO1 = 0, EBO1 = 0;
  glGenVertexArrays(1, &VAO1);
  glBindVertexArray(VAO1);

  glGenBuffers(1, &VBO1);
  glBindBuffer(GL_ARRAY_BUFFER, VBO1);
  glBufferData(GL_ARRAY_BUFFER, trangle_vertices1.size() * sizeof(float), &trangle_vertices1[0], GL_STATIC_DRAW);

  glGenBuffers(1, &EBO1);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);

  GLuint VAO2 = 0, VBO2 = 0, EBO2 = 0;
  glGenVertexArrays(1, &VAO2);
  glBindVertexArray(VAO2);

  glGenBuffers(1, &VBO2);
  glBindBuffer(GL_ARRAY_BUFFER,VBO2);
  glBufferData(GL_ARRAY_BUFFER, trangle_vertices2.size() * sizeof(float), &trangle_vertices2[0], GL_STATIC_DRAW);

  glGenBuffers(1, &EBO2);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices2.size() * sizeof(unsigned int), &indices2[0], GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);


  shaders.CreateShader(Shaders::shader_type::VERTICE);
  shaders.CompileShader(Shaders::shader_type::VERTICE);

  shaders.CreateShader(Shaders::shader_type::FRAGMENT);
  shaders.CompileShader(Shaders::shader_type::FRAGMENT);

  shaders.CreateProgram();
  shaders.DeleteShaders();

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 460");

  float trangle1_color[4] = { 0.0f, 0.7f, 0.1f, 1.0f }; // color for trangle1
  float trangle2_color[4] = { 0.8f, 0.3f, 0.02f, 1.0f }; // color for trangle2
  float size = 1.0f; // scale for trangles
  bool fill = true; // polygon mode


  while (!glfwWindowShouldClose(window)) { // loop of render
	  
	  if (fill)
		  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	  else
		  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	  glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
	  glClear(GL_COLOR_BUFFER_BIT);

	  ImGui_ImplOpenGL3_NewFrame();
	  ImGui_ImplGlfw_NewFrame();
	  ImGui::NewFrame();

	  shaders.UseProgram();
	  glBindVertexArray(VAO1);
	  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		  glUniform1f(glGetUniformLocation(shaders.GetShaderProgram(), "size"), size);
		  glUniform4f(glGetUniformLocation(shaders.GetShaderProgram(), "color"),
			  trangle1_color[0], trangle1_color[1], trangle1_color[2], trangle1_color[3]);
		  glBindVertexArray(0);

	  glBindVertexArray(VAO2);
	  glDrawElements(GL_TRIANGLES, indices2.size(), GL_UNSIGNED_INT, 0);
		  glUniform1f(glGetUniformLocation(shaders.GetShaderProgram(), "size"), size);
		  glUniform4f(glGetUniformLocation(shaders.GetShaderProgram(), "color"), 
			  trangle2_color[0], trangle2_color[1], trangle2_color[2], trangle2_color[3]);
	  glBindVertexArray(0);

	  ImGui::Begin("Triangle settings");
	  ImGui::Checkbox("Draw FRONT_AND_BACK Triangle", &fill);
	  ImGui::SliderFloat("Size", &size, 0.5f, 2.0f);
	  ImGui::ColorEdit4("trangle1_color", trangle1_color);
	  ImGui::ColorEdit4("trangle2_color", trangle2_color);
	  ImGui::End();

	  ImGui::Render();
	  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	  glfwSwapBuffers(window);
	  glfwPollEvents();;
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwTerminate();
  return 0;
}

void WindowResize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void KeyInput(GLFWwindow* window, int key, int scancode, int action, int modes) {
	/* For debug input keys
	std::cout << "key:" << key << " scancode:" << scancode 
		<< " action:" << action << " modes:" << modes << "\n";
	*/

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) { // exit for loop of render if press esc 
		std::cout << "Got esc, clouse EdgaEngine2D \n";
		glfwSetWindowShouldClose(window, true);
	}
}