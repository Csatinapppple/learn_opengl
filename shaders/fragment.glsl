#version 330
in vec2 TexCoords;
in vec3 Normal;
in vec3 Position;

out vec4 FragColor;

uniform sampler2D texture1;
uniform samplerCube skybox;
uniform vec3 cameraPos;

void main() {
	float ratio = 1.00/1.52;
	vec3 I = normalize(Position - cameraPos);
	vec3 R = refract(I, normalize(Normal), ratio);

	FragColor = texture(skybox, R) + texture(texture1, TexCoords);
}

