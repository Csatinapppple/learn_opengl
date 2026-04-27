#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <material.hpp>
#include <light.hpp>

class Shader{
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

	void use();
	
	void setVec3f(const std::string& name, glm::vec3 vec) const{
		GLuint location = glGetUniformLocation(ID, name.c_str());
		glUniform3f(location, vec.x, vec.y, vec.z);
	};
	
	void setMaterial(Material material) {
		GLuint ambientLoc = glGetUniformLocation(ID, "material.ambient");
		GLuint diffuseLoc = glGetUniformLocation(ID, "material.diffuse");
		GLuint specularLoc = glGetUniformLocation(ID, "material.specular");
		GLuint shininessLoc = glGetUniformLocation(ID, "material.shininess");
		glUniform3f(ambientLoc, material.ambient.x, material.ambient.y, material.ambient.z);
		glUniform3f(diffuseLoc, material.diffuse.x, material.diffuse.y, material.diffuse.z);
		glUniform3f(specularLoc, material.specular.x, material.specular.y, material.specular.z);
		glUniform1f(shininessLoc, material.shininess);
	}

	void setLight(Light light) {
		GLuint positionLoc = glGetUniformLocation(ID, "light.position");
		GLuint ambientLoc = glGetUniformLocation(ID, "light.ambient");
		GLuint diffuseLoc = glGetUniformLocation(ID, "light.diffuse");
		GLuint specularLoc = glGetUniformLocation(ID, "light.specular");
		glUniform3f(ambientLoc, light.ambient.x, light.ambient.y, light.ambient.z);
		glUniform3f(diffuseLoc, light.diffuse.x, light.diffuse.y, light.diffuse.z);
		glUniform3f(specularLoc, light.specular.x, light.specular.y, light.specular.z);
		glUniform3f(positionLoc, light.position.x, light.position.y, light.position.z);
	}

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
