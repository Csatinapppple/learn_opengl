#version 330
out vec4 FragColor;

in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
	vec4 first_texture = texture(texture1, texCoord);
	vec4 second_texture = texture(texture2, texCoord);

	FragColor = mix(first_texture, second_texture, 0.5);
}
