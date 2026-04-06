#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Material {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};

const Material MATERIAL_CYAN_PLASTIC = {
	glm::vec3(0.0f, 0.1f, 0.06f),
	glm::vec3(0.0f, 0.50980392f, 0.50980392f),
	glm::vec3(0.50196078f, 0.50196078f, 0.50196078f),
	0.25f
};

const Material MATERIAL_GOLD = {
	glm::vec3(0.24725f, 0.1995f, 0.0745f),
	glm::vec3(0.75164f, 0.60648f, 0.22648f),
	glm::vec3(0.628281f, 0.555802f, 0.366065f),
	0.4f
};

class Shader{
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);

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

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const{
		GLuint location = glGetUniformLocation(ID, name.c_str());
		glUniform1f(location, value);
	};
};

#endif
