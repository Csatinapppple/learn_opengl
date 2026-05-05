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
	void setBool(const std::string& name, bool value) const;

	void setInt(const std::string& name, int value) const {
		GLint location = glGetUniformLocation(ID, name.c_str());
		glUniform1i(location, value);
	}

	void setFloat(const std::string& name, float value) const {
		GLint location = glGetUniformLocation(ID, name.c_str());
		glUniform1f(location, value);
	}
	
	void setSpotLightMut(SpotLight& spotLight){
		GLint directionLoc = glGetUniformLocation(ID, "spotLight.direction");
		GLint positionLoc = glGetUniformLocation(ID, "spotLight.position");
		glUniform3fv(directionLoc, 1, glm::value_ptr(spotLight.direction));
		glUniform3fv(positionLoc, 1, glm::value_ptr(spotLight.position));
	}
	void setSpotLightConsts(SpotLight& spotLight){
		GLint ambientLoc = glGetUniformLocation(ID, "spotLight.ambient");
		GLint diffuseLoc = glGetUniformLocation(ID, "spotLight.diffuse");
		GLint specularLoc = glGetUniformLocation(ID, "spotLight.specular");
		GLint constantLoc = glGetUniformLocation(ID, "spotLight.constant");
		GLint linearLoc = glGetUniformLocation(ID, "spotLight.linear");
		GLint quadraticLoc = glGetUniformLocation(ID, "spotLight.quadratic");
		GLint cutOffLoc = glGetUniformLocation(ID, "spotLight.cutOff");
		GLint outerCutOffLoc = glGetUniformLocation(ID, "spotLight.outerCutOff");
		glUniform3fv(ambientLoc, 1, glm::value_ptr(spotLight.ambient));
		glUniform3fv(diffuseLoc, 1, glm::value_ptr(spotLight.diffuse));
		glUniform3fv(specularLoc, 1, glm::value_ptr(spotLight.specular));
		glUniform1f(constantLoc, spotLight.constant);
		glUniform1f(linearLoc, spotLight.linear);
		glUniform1f(quadraticLoc, spotLight.quadratic);
		glUniform1f(cutOffLoc, spotLight.cutOff);
		glUniform1f(outerCutOffLoc, spotLight.outerCutOff);
	}

	void setDirLight(DirLight& dirLight){
		GLint directionLoc = glGetUniformLocation(ID, "dirLight.direction");
		GLint ambientLoc = glGetUniformLocation(ID, "dirLight.ambient");
		GLint diffuseLoc = glGetUniformLocation(ID, "dirLight.diffuse");
		GLint specularLoc = glGetUniformLocation(ID, "dirLight.specular");
		glUniform3fv(directionLoc, 1, glm::value_ptr(dirLight.direction));
		glUniform3fv(ambientLoc, 1, glm::value_ptr(dirLight.ambient));
		glUniform3fv(diffuseLoc, 1, glm::value_ptr(dirLight.diffuse));
		glUniform3fv(specularLoc, 1, glm::value_ptr(dirLight.specular));
	}

	void setPointLights(PointLight& pointLight, size_t pos, glm::vec3 lightPos) {
		GLint ambientLoc = glGetUniformLocation(
				ID, ("pointLights[" + std::to_string(pos) + "].ambient").c_str());
		GLint diffuseLoc = glGetUniformLocation(
				ID, ("pointLights["+std::to_string(pos)+"].diffuse").c_str());
		GLint specularLoc = glGetUniformLocation(
				ID, ("pointLights["+std::to_string(pos)+"].specular").c_str());
		GLint positionLoc = glGetUniformLocation(
				ID, ("pointLights["+std::to_string(pos)+"].position").c_str());
		GLint constantLoc = glGetUniformLocation(
				ID, ("pointLights["+std::to_string(pos)+"].constant").c_str());
		GLint linearLoc = glGetUniformLocation(
				ID, ("pointLights["+std::to_string(pos)+"].linear").c_str());
		GLint quadraticLoc = glGetUniformLocation(
				ID, ("pointLights["+std::to_string(pos)+"].quadratic").c_str());
		glUniform3fv(ambientLoc, 1, glm::value_ptr(pointLight.ambient));
		glUniform3fv(diffuseLoc, 1, glm::value_ptr(pointLight.diffuse));
		glUniform3fv(specularLoc, 1, glm::value_ptr(pointLight.specular));
		glUniform3fv(positionLoc, 1, glm::value_ptr(lightPos));
		glUniform1f(constantLoc, pointLight.constant);
		glUniform1f(linearLoc, pointLight.linear);
		glUniform1f(quadraticLoc, pointLight.quadratic);
	}
};

#endif
