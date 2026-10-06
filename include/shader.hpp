#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

class Shader{
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath, const char* geomPath = nullptr);

	void use();
	
	void setVec3f(const std::string& name, glm::vec3 vec) const{
		GLint location = glGetUniformLocation(ID, name.c_str());
		glUniform3f(location, vec.x, vec.y, vec.z);
	};

	void set1ui(const std::string& name, unsigned int value) const {
		GLint location = glGetUniformLocation(ID, name.c_str());
		glUniform1ui(location, value);
	}

	void setMatrix4f(const std::string& name, glm::mat4 mat) const{
		GLint location = glGetUniformLocation(ID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}
	
	void setMatrix4fv(const std::string& name, std::vector<glm::mat4>& mats) const{
		GLint location = glGetUniformLocation(ID, name.c_str());
		glUniformMatrix4fv(location, mats.size(), GL_FALSE, glm::value_ptr(mats[0]));
	}

	void setBool(const std::string& name, bool value) const;

	void setInt(const std::string& name, int value) const {
		GLint location = glGetUniformLocation(ID, name.c_str());
		glUniform1i(location, value);
	}

	void setFloat(const std::string& name, float value) const {
		GLint location = glGetUniformLocation(ID, name.c_str());
		glUniform1f(location, value);
	}
	
};

#endif
