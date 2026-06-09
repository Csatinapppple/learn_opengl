#ifndef SCENE_HPP
#define SCENE_HPP

#include <fstream>

#include <glm/glm.hpp>
#include <camera.hpp>
#include <model.hpp>
#include <light.hpp>
#include <curve.hpp>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Scene {
public:
	std::vector<Model> models;
	Camera camera;
	glm::mat4 projection;
	DirLight dirLight;
	std::vector<PointLight> pointLights;
	std::vector<SpotLight> spotLights;

	Scene(const char* json_path){
		std::ifstream f(json_path);
		json data = json::parse(f);

		for (const auto& model_json : data["models"]){
			std::string model_path = model_json["path"].get<std::string>();
			std::optional<Curves> curves = std::nullopt;
			glm::vec3 translate = parse_vec3(model_json["translate"]);
			glm::vec3 rotate = parse_vec3(model_json["rotate"]);
			glm::vec3 scale = parse_vec3(model_json["scale"]);

			if (model_json.contains("curves") && !model_json["curves"].empty()){
				for (const auto& curve : model_json["curves"]) {
					std::vector<glm::vec3> points;
					for (const auto& point : curve) {
						points.push_back(parse_vec3(point));
					}
					curves = Curves(points);
				}
			}
			Model model(
				model_path,
				translate,
				rotate,
				scale,
				curves
			);
			models.push_back(model);
		}
		
		json cameraJson = data["camera"];

		glm::vec3 camera_position = parse_vec3(cameraJson["position"]);
		glm::vec3 camera_front = parse_vec3(cameraJson["front"]);
		glm::vec3 camera_up = parse_vec3(cameraJson["up"]);
		float camera_yaw = cameraJson["yaw"].get<float>();
		float camera_pitch = cameraJson["pitch"].get<float>();
		json frustrum = cameraJson["frustrum"];
		float near = frustrum["near"].get<float>();
		float far = frustrum["far"].get<float>();
		float fov = frustrum["fov"].get<float>();

		camera = Camera(
				camera_position,
				camera_up,
				camera_front,
				camera_yaw,
				camera_pitch,
				fov
		);
		
		projection = glm::perspective(
				glm::radians(fov), 800.0f/600.0f, near, far);

		json lights = data["lights"];
		
		dirLight = parse_dir_light(lights["dirLight"]);
		pointLights = parse_point_lights(lights["pointLights"]);
		spotLights = parse_spot_lights(lights["spotLights"]);

	}

	DirLight parse_dir_light(const json& j) {
		return DirLight {
			.direction = parse_vec3(j["direction"]),
			.position = parse_vec3(j["position"]),
			.ambient = parse_vec3(j["ambient"]),
			.diffuse = parse_vec3(j["diffuse"]),
			.specular = parse_vec3(j["specular"])
		};
	}

	std::vector<PointLight> parse_point_lights(const json& j) {
		std::vector<PointLight> ret;
		for (const auto& pointLight : j){
			PointLight newPointLight{
				.position = parse_vec3(pointLight["position"]),
				.ambient = parse_vec3(pointLight["ambient"]),
				.diffuse = parse_vec3(pointLight["diffuse"]),
				.specular = parse_vec3(pointLight["specular"]),
				.distance = Distance {
					.constant = pointLight["distance"]["constant"].get<float>(),
					.linear = pointLight["distance"]["linear"].get<float>(),
					.quadratic = pointLight["distance"]["quadratic"].get<float>(),
				}
			};

			ret.push_back(newPointLight);
		}
		return ret;
	}

	std::vector<SpotLight> parse_spot_lights(const json& j) {
		std::vector<SpotLight> ret;
		for (const auto& spotLight : j){
			SpotLight newSpotLight{
				.position = parse_vec3(spotLight["position"]),
				.ambient = parse_vec3(spotLight["ambient"]),
				.diffuse = parse_vec3(spotLight["diffuse"]),
				.specular = parse_vec3(spotLight["specular"]),
				.cutOff = spotLight["cutOff"].get<float>(),
				.outerCutOff = spotLight["outerCutOff"].get<float>(),
				.distance = Distance {
					.constant = spotLight["distance"]["constant"].get<float>(),
					.linear = spotLight["distance"]["linear"].get<float>(),
					.quadratic = spotLight["distance"]["quadratic"].get<float>(),
				}
			};

			ret.push_back(newSpotLight);
		}
		return ret;
	}

	glm::vec3 parse_vec3(const json& j) {
		return glm::vec3(j[0].get<float>(), j[1].get<float>(), j[2].get<float>());
	}



};

#endif
