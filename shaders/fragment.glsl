#version 330
out vec4 FragColor;

uniform vec3 objectColor;

in vec3 LightingColor;

void main() {
	FragColor = vec4(LightingColor * objectColor, 1.0);
}
