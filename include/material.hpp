#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

#include <glm/glm.hpp>

struct Material {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};

const Material MAT_EMERALD = {
	glm::vec3(0.0215f, 0.1745f, 0.0215f),
	glm::vec3(0.07568f, 0.61424f, 0.07568f),
	glm::vec3(0.633f, 0.727811f, 0.633f),
	0.6f
};

const Material MAT_JADE = {
	glm::vec3(0.135f, 0.2225f, 0.1575f),
	glm::vec3(0.54f, 0.89f, 0.63f),
	glm::vec3(0.316228f, 0.316228f, 0.316228f),
	0.1f
};

#endif
