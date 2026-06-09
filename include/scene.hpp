#ifndef SCENE_HPP
#define SCENE_HPP

#include <fstream>

#include <glm/glm.hpp>
#include <camera.hpp>
#include <model.hpp>
#include <light.hpp>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Scene {
	public:
	std::vector<Model> models;
	Camera camera;
	DirLight dirLight;
	std::vector<PointLight> pointLights;
	std::vector<SpotLight> spotLights;

	Scene(const char* json_path){
		std::ifstream f(json_path);
		json data = json::parse(f);
	}



};

#endif
