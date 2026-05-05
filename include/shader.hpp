#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

struct DirLight {
	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

struct SpotLight {
	glm::vec3 direction;
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float constant;
	float linear;
	float quadratic;
	float cutOff;
	float outerCutOff;
};

struct PointLight {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float constant;
	float linear;
	float quadratic;
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
	void setBool(const std::string& name, bool value) const;

	void setInt(const std::string& name, int value) const {
		GLuint location = glGetUniformLocation(ID, name.c_str());
		glUniform1i(location, value);
	}

	void setFloat(const std::string& name, float value) const {
		GLuint location = glGetUniformLocation(ID, name.c_str());
		glUniform1f(location, value);
	}
	
	void setSpotLightMut(SpotLight& spotLight){
		GLuint directionLoc = glGetUniformLocation(ID, "spotLight.direction");
		GLuint positionLoc = glGetUniformLocation(ID, "spotLight.position");
		glUniform3f(directionLoc, spotLight.direction.x, spotLight.direction.y, spotLight.direction.z);
		glUniform3f(positionLoc, spotLight.position.x, spotLight.position.y, spotLight.position.z);
	}
	void setSpotLightConsts(SpotLight& spotLight){
		GLuint ambientLoc = glGetUniformLocation(ID, "spotLight.ambient");
		GLuint diffuseLoc = glGetUniformLocation(ID, "spotLight.diffuse");
		GLuint specularLoc = glGetUniformLocation(ID, "spotLight.specular");
		GLuint constantLoc = glGetUniformLocation(ID, "spotLight.constant");
		GLuint linearLoc = glGetUniformLocation(ID, "spotLight.linear");
		GLuint quadraticLoc = glGetUniformLocation(ID, "spotLight.quadratic");
		GLuint cutOffLoc = glGetUniformLocation(ID, "spotLight.cutOff");
		GLuint outerCutOffLoc = glGetUniformLocation(ID, "spotLight.outerCutOff");
		glUniform3f(ambientLoc, spotLight.ambient.x, spotLight.ambient.y, spotLight.ambient.z);
		glUniform3f(diffuseLoc, spotLight.diffuse.x, spotLight.diffuse.y, spotLight.diffuse.z);
		glUniform3f(specularLoc, spotLight.specular.x, spotLight.specular.y, spotLight.specular.z);
		glUniform1f(constantLoc, spotLight.constant);
		glUniform1f(linearLoc, spotLight.linear);
		glUniform1f(quadraticLoc, spotLight.quadratic);
		glUniform1f(cutOffLoc, spotLight.cutOff);
		glUniform1f(outerCutOffLoc, spotLight.outerCutOff);
	}

	void setDirLight(DirLight& dirLight){
		GLuint directionLoc = glGetUniformLocation(ID, "dirLight.direction");
		GLuint ambientLoc = glGetUniformLocation(ID, "dirLight.ambient");
		GLuint diffuseLoc = glGetUniformLocation(ID, "dirLight.diffuse");
		GLuint specularLoc = glGetUniformLocation(ID, "dirLight.specular");
		glUniform3f(directionLoc, dirLight.direction.x, dirLight.direction.y, dirLight.direction.z);
		glUniform3f(ambientLoc, dirLight.ambient.x, dirLight.ambient.y, dirLight.ambient.z);
		glUniform3f(diffuseLoc, dirLight.diffuse.x, dirLight.diffuse.y, dirLight.diffuse.z);
		glUniform3f(specularLoc, dirLight.specular.x, dirLight.specular.y, dirLight.specular.z);
	}

	void setPointLight(PointLight& pointLight, size_t pos, glm::vec3 lightPos) {
		GLuint ambientLoc = glGetUniformLocation(
				ID, ("pointLight[" + std::to_string(pos) + "].ambient").c_str());
		std::cout << ambientLoc << std::endl;
		GLuint diffuseLoc = glGetUniformLocation(
				ID, ("pointLight["+std::to_string(pos)+"].diffuse").c_str());
		GLuint specularLoc = glGetUniformLocation(
				ID, ("pointLight["+std::to_string(pos)+"].specular").c_str());
		GLuint positionLoc = glGetUniformLocation(
				ID, ("pointLight["+std::to_string(pos)+"].position").c_str());
		GLuint constantLoc = glGetUniformLocation(
				ID, ("pointLight["+std::to_string(pos)+"].constant").c_str());
		GLuint linearLoc = glGetUniformLocation(
				ID, ("pointLight["+std::to_string(pos)+"].linear").c_str());
		GLuint quadraticLoc = glGetUniformLocation(
				ID, ("pointLight["+std::to_string(pos)+"].quadratic").c_str());
		glUniform3f(ambientLoc, pointLight.ambient.x, pointLight.ambient.y, pointLight.ambient.z);
		glUniform3f(diffuseLoc, pointLight.diffuse.x, pointLight.diffuse.y, pointLight.diffuse.z);
		glUniform3f(specularLoc, pointLight.specular.x, pointLight.specular.y, pointLight.specular.z);
		glUniform3f(positionLoc, lightPos.x, lightPos.y, lightPos.z);
		glUniform1f(constantLoc, pointLight.constant);
		glUniform1f(linearLoc, pointLight.linear);
		glUniform1f(quadraticLoc, pointLight.quadratic);
	}
};

#endif
