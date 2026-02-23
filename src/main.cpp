#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fileReader.hpp>

void bindBuffersWithSizeAndData(GLuint VBOId, GLuint VAOId, GLsizeiptr size, const void* data);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

void handleId(unsigned int shaderId, GLenum pname);

float vertices[] = {
	-0.75f, -0.5f, 0.0f,
	-0.25f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,

	0.75f, -0.5f, 0.0f,
	0.25f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f
};


int main() {
	
	std::string shaderSource = read_file("./src/shaders/vertex.glsl");
	std::string fragmentSource = read_file("./src/shaders/fragment.glsl");
	std::string fragmentSource2 = read_file("./src/shaders/fragment2.glsl");
	const char *vertexShaderSource = shaderSource.c_str();
	const char *fragmentShaderSource = fragmentSource.c_str();
	const char *fragmentShaderSource2 = fragmentSource2.c_str();
	
	if (!glfwInit()) return -1;
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "learn opengl", NULL, NULL);
	
	if (window == NULL){
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	handleId(vertexShader, GL_COMPILE_STATUS);

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
		
	handleId(fragmentShader, GL_COMPILE_STATUS);

	unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShader2);
		
	handleId(fragmentShader2, GL_COMPILE_STATUS);

	GLuint shaderPrograms[2];
	
	shaderPrograms[0] = glCreateProgram();

	glAttachShader(shaderPrograms[0], vertexShader);
	glAttachShader(shaderPrograms[0], fragmentShader);
	glLinkProgram(shaderPrograms[0]);

	handleId(shaderPrograms[0], GL_LINK_STATUS);
	
	glDeleteShader(fragmentShader);

	shaderPrograms[1] = glCreateProgram();

	glAttachShader(shaderPrograms[1], vertexShader);
	glAttachShader(shaderPrograms[1], fragmentShader2);
	glLinkProgram(shaderPrograms[1]);

	handleId(shaderPrograms[1], GL_LINK_STATUS);
	
	glDeleteShader(fragmentShader2);
	glDeleteShader(vertexShader);

	GLuint  VBO[2],
				  VAO[2];

	glGenBuffers(2, VBO);
	glGenVertexArrays(2, VAO);

	
	bindBuffersWithSizeAndData(VBO[0], VAO[0], sizeof(vertices) / 2, vertices);
	bindBuffersWithSizeAndData(VBO[1], VAO[1], sizeof(vertices) / 2, vertices+9);

	while(!glfwWindowShouldClose(window)){
		processInput(window);
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		
		for (int i = 0; i < 2; i++){
			glUseProgram(shaderPrograms[i]);
			glBindVertexArray(VAO[i]);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

void bindBuffersWithSizeAndData(GLuint VBOId, GLuint VAOId, GLsizeiptr size, const void* data_start) {
	glBindVertexArray(VAOId);
	glBindBuffer(GL_ARRAY_BUFFER, VBOId);
	glBufferData(GL_ARRAY_BUFFER, size, data_start, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}  

void handleId(unsigned int id, GLenum pname) {
	int success;
	char infoLog[512];

	switch (pname) {
		case GL_LINK_STATUS:
			glGetProgramiv(id, pname, &success);
			if (!success) {
				glGetProgramInfoLog(id, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
			}
			break;
		case GL_COMPILE_STATUS:
			glGetShaderiv(id, pname, &success);
			if (!success) {
				glGetShaderInfoLog(id, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
			}
			break;
	}
}

void processInput(GLFWwindow *window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
