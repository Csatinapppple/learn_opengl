#version 330
out vec4 FragColor;

in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
	
	vec2 reverse_coord = vec2(texCoord.x * -1.0, texCoord.y);

	vec4 first_texture = texture(texture1, texCoord);
	vec4 second_texture = texture(texture2, reverse_coord);

	FragColor = mix(first_texture, second_texture, 0.5);
}
