#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader{
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath);

	void use();
	
	void setVec3f(const std::string& name, glm::vec3 vec) const{
		GLuint location = glGetUniformLocation(ID, name.c_str());
		glUniform3f(location, vec.x, vec.y, vec.z);
	};

	void set1ui(const std::string& name, unsigned int value) const {
		GLuint location = glGetUniformLocation(ID, name.c_str());
		glUniform1ui(location, value);
	}

	void setMatrix4f(const std::string& name, glm::mat4 mat) const{
		GLuint location = glGetUniformLocation(ID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}
	void setBool(const std::string& name, bool value) const{
		GLuint location = glGetUniformLocation(ID, name.c_str());
		glUniform1i(location, value);
	};
	void setInt(const std::string& name, int value) const{
		GLuint location = glGetUniformLocation(ID, name.c_str());
		glUniform1i(location, value);
	};
	void setFloat(const std::string& name, float value) const{
		GLuint location = glGetUniformLocation(ID, name.c_str());
		glUniform1f(location, value);
	};
};

#endif
