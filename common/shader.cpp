#include <shader.hpp>
#include <fileReader.hpp>

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

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


Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geomPath) {
	std::string vertexCode = read_file(vertexPath);
	std::string fragmentCode = read_file(fragmentPath);
	std::string geomCode;
	if(geomPath != nullptr)
		geomCode = read_file(geomPath);

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	const char* gShaderCode;
	if(geomPath != nullptr)
		gShaderCode = geomCode.c_str();
	
	unsigned int vertex, fragment, geom;
	
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	handleId(vertex, GL_COMPILE_STATUS);
	
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	handleId(fragment, GL_COMPILE_STATUS);

	if (geomPath != nullptr){
		geom = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geom, 1, &gShaderCode, NULL);
		glCompileShader(geom);
		handleId(geom, GL_COMPILE_STATUS);
	}
	
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	if (geomPath != nullptr) glAttachShader(ID, geom);
	glLinkProgram(ID);
	handleId(ID, GL_LINK_STATUS);
	
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	if (geomPath != nullptr) glDeleteShader(geom);
}

void Shader::use() {
	glUseProgram(ID);
}
