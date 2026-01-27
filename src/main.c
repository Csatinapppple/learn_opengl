#include <GLFW/glfw3.h>
#include <stdio.h>
#include "../include/glad/glad.h"


int main() {
	

	printf("Window memory fuck");
	GLFWwindow* window = glfwCreateWindow(640, 480, "fuckass title", NULL, NULL);
	
	if (window == NULL){
		printf("epic fail");
	}
	
	printf("Window memory %p", window);

	while(1);

	return 0;
}
