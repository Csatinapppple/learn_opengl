//#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdio.h>


int main() {
	
	if (!glfwInit()) return -1;
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	printf("Window memory fuck");
	GLFWwindow* window = glfwCreateWindow(640, 480, "fuckass title", NULL, NULL);
	
	if (window == NULL){
		printf("epic fail");
	}
	
	printf("Window memory %p", window);

	while(1);

	return 0;
}
